#include "bmp.h"

//file header info
FILE_HEADER f_header;
INFO_HEADER inf_header;

void print_col(Color *c){
    printf("R=%x,G=%x,B=%x\n",c->r,c->g,c->b);
}

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
//    if (f_header.ident[0] != 'B' && f_header.ident[1] != 'M') {
//        printf("Invalid BMP file header");
//        return NULL;
//    }
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

//    //convert the pixel array in-place from bgr colour space to rgb color space
//    convert_to_rgb(img);
//
//    //reverse pixel array
//    reverse_pixel_array(img);

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

//print out pixel data to std out omitting padded bytes for debugging purposes
void print_pixel_array(IMAGE *img) {
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {

        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {

            printf("\n");
            row_pos = 0; 			    //reset the row count.
            i = i + img->padding - 1; 	//skip padding, minus 1 because
            continue;   			    //for condition will add 1 to i;
        }
        unsigned char b = img->pixel_array[i++];
        unsigned g = img->pixel_array[i++];
        unsigned r = img->pixel_array[i];
        printf("R=%x \tG=%x \tB=%x\n",r,g,b);
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
}

//convert the pixel array in-place from blue, green, red colour space, to the red, green, blue colour space
void convert_to_rgb(IMAGE *img) {
    int i;
    int row_pos = 0;
    int flag = 0;
    unsigned char temp = 0;
    enum colour {BLUE, GREEN, RED};

    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size; i++) {
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length) {
            row_pos = 0; 			//reset the row position count.
            i = i + img->padding - 1; 	//skip padding, minus 1 because
            continue;   			//for condition will add 1 to i;
        }

        //put the blue value into a temp variable
        if (flag == BLUE) {
            temp = img->pixel_array[i];
            flag = GREEN; // change flag to GREEN for processing the green value

            //green is already in place don't need to do anything
        } else if( flag == GREEN) {

            flag = RED;// change flag to RED for processing the red value

            //put the red value into the blue's old place. and the temp value in the red's place
        } else {
            img->pixel_array[i - 2] = img->pixel_array[i];
            img->pixel_array[i] = temp;
            flag = BLUE; // reset flag back to BLUE to start the cycle again.
        }
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
}

//this reverses the pixel array because BMP files by definition are stored upside down
//possible optimisation using memcpy() function instead of swapping byte for byte.
void reverse_pixel_array(IMAGE *img) {
    int i;
    int temp = 0;
    int row_pos = 0; //byte position in current row
    int row_count = 1; //we always start from the 1st row
    int opposite_row_i = (img->row_length + img->padding) * (img->height - row_count); //the array index opposite to the current index
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size / 2; i++) {
        // skip the loop count ahead of the padded bytes
        // put index counters at their correct positions so the algorithm works correctly
        if (row_pos == img->row_length) {
            //which row in the image we are at
            row_count++;
            //the index to the start of the opposite row to the current row index
            opposite_row_i = (img->row_length + img->padding) * (img->height - row_count);
            //reset the row position count. (which byte in the current row we're at)
            row_pos = 0;
            //skip padding, minus 1 because the for condition will add 1 to the index;
            i = i + img->padding - 1;
            continue;
        }

        //swap one row of pixels with the opposite row. eg first row with last row. second with second last
        temp = img->pixel_array[i];
        img->pixel_array[i] = img->pixel_array[opposite_row_i];
        img->pixel_array[opposite_row_i] = temp;
        opposite_row_i++;
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
}

//This returns the bbp of the loaded image as an integer.
//uses a 32bit int to avoid integer overflow.
uint16_t get_colour_depth(IMAGE *img){
    uint32_t depth = img->bbp;
    return depth;
}

char* my_substring(const char *string,int position, int length){
    char *sub = malloc(length+1*sizeof(char));
    int c = 0;
    while (c < length) {
        sub[c] = string[position+c];
        c++;
    }
    sub[c] = '\0';
    return sub;
}

int get_offset_in_data(int x, int y, int img_w, int img_h) {
    int padding_per_row = 4 % img_w;
    int row_start_idx = (img_h-y)*img_w*3+((img_h-y)*padding_per_row*3);
    int idx_in_row = 3*x;
//    printf("%d + %d\n",row_start_idx,idx_in_row);
    return row_start_idx+idx_in_row;
}

Color *get_pixel_color(IMAGE* image, int x, int y) {
    char r,g,b;
    int offset = get_offset_in_data(x,y,image->width,image->height);
    b = image->pixel_array[offset];
    g = image->pixel_array[offset+1];
    r = image->pixel_array[offset+2];

    Color pixel_col = {r,g,b};
    Color *p = &pixel_col;
    return p;
}

