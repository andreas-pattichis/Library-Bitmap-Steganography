#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Struct that represents a color.
 */
typedef struct {
    char r, g, b;
} Color;

/**
 * Struct that represents the BitMap File Header of the image
 */
typedef struct {
    uint16_t  ident;             // Magic identifier: 0x4d42
    uint32_t  file_size;             // File size in bytes
    uint16_t  reserve_1;        // Not used
    uint16_t  reserve_2;        // Not used
    uint32_t  pix_array_offset;           // Offset to image data in bytes from beginning of file (54 bytes)
} FILE_HEADER;

/**
 * Struct that represents the BitMap Info Header of the image
 */
typedef struct {

    uint32_t  size;  // DIB Header size in bytes (40 bytes)
    int32_t   width;         // Width of the image
    int32_t   height;        // Height of image
    uint16_t  colour_plain;       // Number of color planes
    uint16_t  bbp;   // Bits per pixel
    uint32_t  compression_method;      // Compression type
    uint32_t  img_size; // Image size in bytes
    int32_t   horizontal_res; // Pixels per meter
    int32_t   vertical_res; // Pixels per meter
    uint32_t  num_colours;       // Number of colors
    uint32_t  important_colours; // Important colors
} INFO_HEADER;

/**
 * Struct to hold all necessary image data
 */
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

void print_col(Color *c);

/**
 * Method that will store the image data in the struct IMAGE
 *
 * @param file_name
 * @return
 */
IMAGE* load_bmp(const char *file_name);

/**
 * Method to free the memory used by the images pixel data
 */
void free_img(unsigned char *pixel_array, IMAGE *img);

/**
 * Method to print out pixel data to std out omitting padded bytes
 *
 * @param img
 */
void print_pixel_array(IMAGE *img);

/**
 * Method to convert the pixel array in-place from blue, green, red colour space, to the red, green, blue colour space
 */
extern void convert_to_rgb(IMAGE *img);

/**
 * Method to reverse the pixel array because BMP files by definition are stored upside down
 * @param img
 */
extern void reverse_pixel_array(IMAGE *img);

/**
 * Method to get the colour depth for the currently loaded image as integer.
 */
extern uint16_t get_colour_depth(IMAGE *img);

char* my_substring(const char *string,int position, int length);

int get_offset_in_data(int x, int y, int img_w, int img_h);

Color *get_pixel_color(IMAGE* image, int x, int y);


/**
 * Prints a list displaying all the information of the BMP Image
 * @param img
 */
void print_information(IMAGE *img);