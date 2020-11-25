/*
#include "Library.h"

void decode_image(IMAGE *img,unsigned int proof_len){
    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int new_arr_length = img->pixel_array_size;
    //   memcpy(new_pixel_array,img->pixel_array,new_arr_length);
    unsigned char r,g,b;
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			        // reset the row count.
            i = i + img->padding - 1;   	// skip padding, minus 1 because
            continue;   			        // for condition will add 1 to i;
        }
        b = img->pixel_array[i];
//        printf("Original is %x\n",b);
        b = b << (8-proof_len);
//        printf("After << is %x\n",b);
//        b = b & calculate_mask(proof_len);
//        printf("Final is %x\n",b);
        new_pixel_array[i] = b;
        i++;
        g = img->pixel_array[i];
        g = g << (8-proof_len);
//        g = g & calculate_mask(proof_len);
        new_pixel_array[i] = g;
        i++;
        r = img->pixel_array[i];
        r = r << (8-proof_len);
//        r = r & calculate_mask(proof_len);
        new_pixel_array[i] = r;

        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
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
    FILE *file = fopen("decoded.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}
 */