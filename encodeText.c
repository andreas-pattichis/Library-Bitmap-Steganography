/*
#include "encodeText.h"

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

int *createPermutationFunction(int n, unsigned int system_key){
    srand(system_key);
    int temp;
    int *arr = calloc(n,sizeof(int));
    // fill array with values
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int a = rand() % n;
        int b = rand() % n;
        temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
    return arr;
}

void putTextInPicture(IMAGE *img, char *text, unsigned int system_key){

    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    memcpy(new_pixel_array,img->pixel_array,img->pixel_array_size);
    int b,o,n = (1+strlen(text))*8,*permutations = createPermutationFunction(n,system_key);

    for (int i = 0; i < (1+strlen(text))*8; i++) {
        b = getBit(text,i);
        o = permutations[i];
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
}*/