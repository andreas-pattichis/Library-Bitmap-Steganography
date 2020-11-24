#include "stringToImage.h"

int getBit(char *m, int n){
    if(n>=0 && n<=8*strlen(m)) {
        int i = n / 8;
        char ch = m[i];
        int bitStatus;
        bitStatus = (ch >> 7 - (n % 8)) & 1;
        return bitStatus;
    }
    return 0;
}

void stringToImage(IMAGE *img, char *textFile){
    char text[img->height * img->width];

    FILE *filePointer;

    filePointer = fopen(textFile, "r");
    if (filePointer == NULL){
        printf("File is not available \n");
        return;
    }

    int cnt = 0;
    while ((fgetc(filePointer)) != EOF) {
        if (cnt < (img->height * img->width)/8) {
            cnt++;
        }
    }
    fclose(filePointer);

    filePointer = fopen(textFile, "r");
    if (filePointer == NULL){
        printf("File is not available \n");
        return;
    }
    int i=0;
    char ch;
    while (i<=cnt) {
        ch = fgetc(filePointer);
        text[i] = ch;
        i++;
    }
    fclose(filePointer);

    /* CHECKING IF THE FILE HAS BEEN READ CORRECTLY
    printf("\n\n%d\n\n",cnt);
    for(i=0;i<=cnt;i++)
        printf("%c",text[i]);
    printf("\n");
    */

    int bits[cnt*8+1];

    for(i=0;i<=cnt*8;i++){
        bits[i] = 128 * getBit(text, img->height * (i / img->height) + (i % img->width));
        /* TESTING TO SEE IF THE BITS HAVE BEEN
        //printf("%d\t",bits[i]);*/
    }
    int k=0;

    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			    // reset the row count.
            i = i + img->padding - 1; 	// skip padding, minus 1 because
            //k++;
            continue;   			    // for condition will add 1 to i;
        }

        if(bits[k]==128){
            new_pixel_array[i++] = (unsigned char)(128);
            new_pixel_array[i++] = (unsigned char)(128);
            new_pixel_array[i] = (unsigned char)(128);
        }
        else{
            new_pixel_array[i++] = (unsigned char)(0);
            new_pixel_array[i++] = (unsigned char)(0);
            new_pixel_array[i] = (unsigned char)(0);
        }
        k++;
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
    IMAGE *new = (IMAGE *)malloc(sizeof(IMAGE));
    new->padding = img->padding;
    new->row_length = img->row_length;
    new->pixel_array_size = img->pixel_array_size;
    new->width = img->width;
    new->height = img->height;
    new->bbp = img->bbp;
    new->pixel_array = new_pixel_array;
    // Save file
    reverse_pixel_array(new);
    FILE *file = fopen("zitima7.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new->pixel_array_size, file);
    fclose(file);
}