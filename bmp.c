#include "bmp.h"

//file header info
FILE_HEADER f_header;
INFO_HEADER inf_header;

IMAGE* load_bmp(const char *file_name) {
    IMAGE *img;
    img = malloc(sizeof(IMAGE));
    if (img == NULL) {
        printf("Error allocating memory for image structure");
        return NULL;
    }
    //image file to process
    FILE *fp;
    fp = fopen(file_name,"rb");
    if (fp == NULL) {
        printf("error opening file");
        return NULL;
    }
    //read file headers
    fread (&f_header, sizeof(FILE_HEADER), 1, fp);
    fread (&inf_header, sizeof(INFO_HEADER), 1, fp);
    fclose(fp);
    // Convert file header info to appropriate types
    uint32_t *pix_array_offset = &f_header.pix_array_offset;
    uint32_t *img_width = &inf_header.width;
    uint32_t *img_height = &inf_header.height;
    uint32_t *img_size = &inf_header.img_size;
    uint16_t *bbp = &inf_header.bbp;
    //24bit pixels only (bytes)
    unsigned int row_size = (*bbp / 8) * *img_width;
    //padding size (bytes)
    unsigned int padding = *img_width % 4;
    //populate image struct
    img->padding = padding;
    img->row_length = row_size;
    img->width = *img_width;
    img->height = *img_height;
    img->pixel_array_size = *img_size;
    img->bbp = *bbp;
    //allocate the pixel buffer
    img->pixel_array = malloc(*img_size);
    //get pixel data from file and copy it into the buffer
    fp = fopen(file_name,"rb");
    fseek(fp,pix_array_offset[0],SEEK_SET);
    fread (img->pixel_array, *img_size, 1, fp);
    fclose(fp);
    if (img->bbp > 24){  //Warn user if they load an image with a higher than 24bit bbp.
        printf("You have loaded a bmp with a higher than 24bit colourdepth.\nSome things may not behave correctly.\n");
    }
    img->file_head = &f_header;
    img->info_head = &inf_header;
    return img;
}

//free the pixel data from memory
void free_img(unsigned char *pixel_array, IMAGE *img) {
    free(pixel_array);
    free(img);
}