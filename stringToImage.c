/*
#include "Library.h"


void stringToImage(IMAGE *img, char *textFileName){
    char text[(img->height * img->width)/8];    // why

    FILE *filePointer;

    filePointer = fopen(textFileName, "r");
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
    // cnt is how many characters we can put into the image
    fclose(filePointer);

    filePointer = fopen(textFileName, "r");
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
    // now we have put our text in the array
    fclose(filePointer);

    // CHECKING IF THE FILE HAS BEEN READ CORRECTLY
//    printf("\n\n%d\n\n",cnt);
//    for(i=0;i<=cnt;i++)
//        printf("%c",text[i]);
//    printf("\n");
//    for (int j = 0; j < cnt; ++j) {
//        printf("%c",text[j]);
//    }


    int bits[cnt*8];
    for(int ii=0;ii<cnt*8;ii++){
        bits[ii] = 128 * getBit(text,ii /*img->height * (i / img->height) + (i % img->width)*//*);

        // TESTING TO SEE IF THE BITS HAVE BEEN
        // printf("%d\t",bits[ii]);
        //bits array is correct
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
//    for (int j = 0; j < 24; j+=3) {
//        if (j % 8 == 0){
//            printf("\n");
//        }
//        printf("new_pixel_array[%d] = %d\n",j,new_pixel_array[j]);
//    }
//pixel array is correct
    IMAGE *new = (IMAGE *)malloc(sizeof(IMAGE));
    new->padding = img->padding;
    new->row_length = img->row_length;
    new->pixel_array_size = img->pixel_array_size;
    new->width = img->width;
    new->height = img->height;
    new->bbp = img->bbp;
    new->pixel_array = new_pixel_array;
    // Save file
//    reverse_pixel_array(new);
    FILE *file = fopen("zitima7.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new->pixel_array_size, file);
    fclose(file);
}
*/