/**
 *  @file bmp.h
 *  @brief Class that represents a BMP image..
 *
 *  @author Costa Christian (), Andreas Pattichis (apatti01)
 *  @bug No know bugs.
 */

#ifndef HOMEWORK4_BMP_H
#define HOMEWORK4_BMP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * @brief Struct that represents the BitMap File Header of the image
 */
typedef struct {
    char ident[2];      // bfType: Will declare if the image is a .bmp file
    char file_size[4];  // bfSize: Specifies the size of the file (including padding) in bytes
    char reserve_1[2];  // Usually set to zero
    char reserve_2[2];  // Usually set to zero
    char pix_array_offset[4]; // bfOffBits: Specifies the offset from the beginning of the file to the bitmap data
} FILE_HEADER;

/**
 * @brief Struct that represents the BitMap Info Header of the image
 */
typedef struct {
    char size[4]; // biSize: Specifies the size of the BITMAPINFOHEADER structure, in bytes
    char width[4]; // biWidth: Specifies the width of the image, in pixels.
    char height[4]; // biHeight: Specifies the height of the image, in pixels.
    char colour_plain[2];
    char bbp[2]; // biBitCount: colour depth (number of bits per pixel)
    char compression_method[4]; // biCompression: Specifies the type of compression
    char img_size[4]; 	//biSizeImage: raw bitmap size (size of image data)
    char horizontal_res[4];
    char vertical_res[4];
    char num_colours[4]; 		//colours in colour pallet
    char important_colours[4];
} INFO_HEADER;

/**
 * @brief Struct to hold all necessary image data
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

/**
 * @brief Method that will store the image data in the struct IMAGE
 *
 * @param file_name
 * @return
 */
IMAGE* load_bmp(const char *file_name);

/**
 * @brief Method to free the memory used by the images pixel data
 */
void free_img(unsigned char *pixel_array, IMAGE *img);

#endif //HOMEWORK4_BMP_H