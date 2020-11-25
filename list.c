/*
#include "Library.h"

int convert_to_anInteger(char *arr, int arrLen){
    int sum = 0,power = arrLen*8 - 1,to_and,which = 0,pos = 7,t,add;
    // reverse the arr because of little endian
    if (arrLen == 2){
        t = arr[0];
        arr[0] = arr[1];
        arr[1] = t;
    }
    else {
        t = arr[0];
        arr[0] = arr[3];
        arr[3] = t;
        t = arr[1];
        arr[1] = arr[2];
        arr[2] = t;
    }
    while (1){
        to_and = arr[which] & (int) pow(2,pos);
        if (to_and != 0 )
            to_and = 1;
        add = to_and * pow(2,power);
//        printf("adding : %d (%d * %d^%d)  Which is : %d  Pos is: %d\n",add,to_and,2,power,which,pos);
        sum += add;
        if (pos % 8 == 0){
            pos = 8;
            which++;
        }
        pos--;
        power--;
        if (which == arrLen){
            break;
        }
    }
    return sum;
}

void print_information(IMAGE *img){

    int BMbfSize = convert_to_anInteger(img->file_head->file_size,4);
    int bfReserved1 = convert_to_anInteger(img->file_head->reserve_1,2);
    int bfReserved2 = convert_to_anInteger(img->file_head->reserve_2,2);
    int bfOffBits = convert_to_anInteger(img->file_head->pix_array_offset,4);
    int biSize = convert_to_anInteger(img->info_head->size,4);
    int biWidth = convert_to_anInteger(img->info_head->width,4);
    int biHeight = convert_to_anInteger(img->info_head->height,4);
    int biPlanes = convert_to_anInteger(img->info_head->colour_plain,2);
    int biBitCount = convert_to_anInteger(img->info_head->bbp,2);
    int biCompression = convert_to_anInteger(img->info_head->compression_method,4);
    int biSizeImage = convert_to_anInteger(img->info_head->img_size,4);
    int biXPelsPerMeter = convert_to_anInteger(img->info_head->horizontal_res,4);
    int biYPelsPerMeter = convert_to_anInteger(img->info_head->vertical_res,4);
    int biClrUsed = convert_to_anInteger(img->info_head->num_colours,4);
    int biClrImportant = convert_to_anInteger(img->info_head->important_colours,4);

    printf("BITMAP_FILE_HEADER\n");
    printf("==================\n");
    printf("bfType: BM\n");
    printf("BMbfSize: %d\n", BMbfSize);
    printf("bfReserved1: %d\n", bfReserved1);
    printf("bfReserved2: %d\n", bfReserved2);
    printf("bfOffBits: %d\n", bfOffBits);
    printf("\nBITMAP_INFO_HEADER\n");
    printf("==================\n");
    printf("biSize: %d\n",biSize);
    printf("biWidth: %d\n",biWidth);
    printf("biHeight: %d\n",biHeight);
    printf("biPlanes: %d\n",biPlanes);
    printf("biBitCount: %d\n",biBitCount);
    printf("biCompression: %d\n",biCompression);
    printf("biSizeImage: %d\n",biSizeImage);
    printf("biXPelsPerMeter: %d\n",biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n",biYPelsPerMeter);
    printf("biClrUsed: %d\n",biClrUsed);
    printf("biClrImportant: %d\n",biClrImportant);
    printf("\n***************************************************************************\n");
}

*/