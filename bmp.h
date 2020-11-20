#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char r, g, b;
} Color;

//BMP header//
typedef struct {
    char ident[2];
    char file_size[4];
    char reserve_1[2];
    char reserve_2[2];
    char pix_array_offset[4];
} FILE_HEADER;

//DIB Header//
typedef struct {
    char size[4];
    char width[4];
    char height[4];
    char colour_plain[2];
    char bbp[2];			//colour depth
    char compression_method[4];
    char img_size[4]; 		//raw bitmap size
    char horizontal_res[4];
    char vertical_res[4];
    char num_colours[4]; 		//colours in colour pallet
    char important_colours[4];
} INFO_HEADER;

//structure to hold all necessary image data
typedef struct{
    FILE_HEADER *file_head;
    INFO_HEADER *info_head;
    unsigned char *pixel_array;
    int padding;
    int pixel_array_size;
    uint32_t width;
    uint32_t height;
    uint32_t row_length;
    uint32_t bbp;
} IMAGE;

//print out pixel data to std out omitting padded bytes
void print_pixel_array(IMAGE *img);

//convert the pixel array in-place from blue, green, red colour space, to the red, green, blue colour space
extern void convert_to_rgb(IMAGE *img);

//this reverses the pixel array because BMP files by definition are stored upside down
extern void reverse_pixel_array(IMAGE *img);

//load bmp file image data into a struct
IMAGE* load_bmp(const char *file_name);

//free the memory used by the images pixel data
void free_img(unsigned char *pixel_array, IMAGE *img);

//get the colour depth for the currently loaded image as integer.
extern uint16_t get_colour_depth(IMAGE *img);

Color *get_pixel_color(IMAGE* image, int x, int y);

int get_offset_in_data(int x, int y, int img_w, int img_h);

char* my_substring(const char *string,int position, int length);

void print_col(Color *c);
