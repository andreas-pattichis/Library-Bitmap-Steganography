/*
#include "Library.h"


void imageToString(IMAGE *img){
//    for (int j = 0; j < 24; j+=3) {
//        if (j % 8 == 0){
//            printf("\n");
//        }
//        printf("new_pixel_array[%d] = %d\n",j,img->pixel_array[j]);
//    }



    int i,sum = 0;
    int row_pos = 0;
    char ch;
    int num;
//    int num1 = 0,num2 = 0,num3 = 0,num4 = 0,num5 = 0,num6 = 0,num7 = 0,num8 = 0;
    FILE *fout = fopen("zitima8.txt","w");

    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-24; i+=24) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
//        if (row_pos == img->row_length/3) {
//            printf("\n");
//            row_pos = 0; 			    // reset the row count.
//            i = i + img->padding - 1; 	// skip padding, minus 1 because
//            //k++;
//            continue;   			    // for condition will add 1 to i;
//        }

        for (int g = 0, po = 7; g <= 21; po--, g+=3) {
//            printf("pixel_array[%d] = %d\n",i+g,img->pixel_array[i+g]);
            num = img->pixel_array[i+g];
            if (num != 0 ){
                num = 1*pow(2,po);
//                printf ("doing 1*2^%d\n",po);
            }
            sum+=num;
//            printf("sum is now: %d\n",sum);
        }
//        num1 = img->pixel_array[i];
//        num2 = img->pixel_array[i+3]>>1;
//        num3 = img->pixel_array[i+6]>>2;
//        num4 = img->pixel_array[i+9]>>3;
//        num5 = img->pixel_array[i+12]>>4;
//        num6 = img->pixel_array[i+15]>>5;
//        num7 = img->pixel_array[i+18]>>6;
//        num8 = img->pixel_array[i+21]>>7;
//        printf("sum is: %d\n",sum);
        ch =  sum;
//        printf("character is: %c\n",ch);
        printf("%c",ch);
        fprintf(fout,"%c",ch);
        row_pos++;
        sum = 0;
    }
    fclose(fout);
}
 */