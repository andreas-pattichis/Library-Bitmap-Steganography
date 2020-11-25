/*
#include "Library.h"

void createGrayscale(IMAGE *img) {
    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			    //reset the row count.
            i = i + img->padding - 1; 	        //skip padding, minus 1 because
            continue;   			    //for condition will add 1 to i;
        }

        int sum = (unsigned char)(0.114* img->pixel_array[i] + 0.587* img->pixel_array[i+1] + 0.299*img->pixel_array[i+2]);
        new_pixel_array[i++] = (unsigned char)(sum );
        new_pixel_array[i++] = (unsigned char)(sum );
        new_pixel_array[i] = (unsigned char)(sum );

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
    FILE *file = fopen("grayscaled.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}
*/