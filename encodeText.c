/*
#include "Library.h"

char *readTextFromFile(char *filename){
    int c1;
    char c,*text;
    int index = 0;
    FILE * fp;
    fp = fopen (filename, "r");
    if (fp==NULL){
        printf("No such file.");
        return NULL;
    }
    text = (char *)calloc(5000,sizeof(char));
    while (1){
        c1 = fgetc(fp);
        if (c1 == EOF){
            break;
        }
        if (c1 == '\r'){
            continue;
        }
        c = c1;
        text[index] = c;
        index++;
    }
    text[index] = '\0';
    fclose(fp);
//    printf("%s\n",text);
    // We know that im getting the text correctly
    return text;
}

void putTextInPicture(IMAGE *img, char *text, unsigned int system_key){

//   unsigned char c = 'a';
//    int ii = 0;
//    while (c != '\0'){
//        c = text[ii];
//
//        printf("%d [%c] -> %d\n",ii,c,c);
//        ii++;
//    }






    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    memcpy(new_pixel_array,img->pixel_array,img->pixel_array_size);
    int b,o,n = (1+strlen(text))*8,*permutations = createPermutationFunction(n,system_key);
//    printf("arr is: %d and len is %d\n",n,strlen(text));
    for (int i = 0; i < (1+strlen(text))*8; i++) {
        b = getBit(text,i);
        o = permutations[i];
//        printf("%d\n",o);
        new_pixel_array[o] = new_pixel_array[o] & 254;
        new_pixel_array[o] = new_pixel_array[o] | b;
    }
    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;
    // Save file
    FILE *file = fopen("withEncodedText.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}
*/