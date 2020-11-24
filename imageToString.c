/*
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

void imageToString(IMAGE *img){
    int i,k=0;
    int row_pos = 0;
    char ch;
    int num1 = 0,num2 = 0,num3 = 0,num4 = 0,num5 = 0,num6 = 0,num7 = 0,num8 = 0;
    FILE *fout = fopen("zitima8.txt","a+");

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

        num1 = img->pixel_array[i];
        num2 = img->pixel_array[i+3]>>1;
        num3 = img->pixel_array[i+6]>>2;
        num4 = img->pixel_array[i+9]>>3;
        num5 = img->pixel_array[i+12]>>4;
        num6 = img->pixel_array[i+15]>>5;
        num7 = img->pixel_array[i+18]>>6;
        num8 = img->pixel_array[i+21]>>7;

        ch =  num1+num2+num3+num4+num5+num6+num7+num8;
        fprintf(fout,"%c",ch);
        row_pos++;
    }
    fclose(fout);
}*/