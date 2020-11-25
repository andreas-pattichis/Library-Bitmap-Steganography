//Header file that contains all the methods for all the operations
#ifndef HOMEWORK4_LIBRARY_H
#define HOMEWORK4_LIBRARY_H
#define MAX_WORDS 5000
#include "CommonFunctions.h"

// OPERATION 1: LIST
/**
 *
 * @param arr
 * @param arrLen
 * @return
 */
int convert_to_anInteger(char *arr, int arrLen);

/**
 *
 * @param img
 */
void print_information(IMAGE *img);

// OPERATION 2: GRAYSCALE
/**
 *
 * @param img
 */
void createGrayscale(IMAGE *img, char *name);

// OPERATION 3: ENCODE_STEGANOGRAPHY
/**
 *
 * @param proof_length
 * @return
 */
unsigned char calculate_mask(unsigned int proof_length);

/**
 *
 * @param cover
 * @param secret
 * @param proof_len
 */
void change_pixels(IMAGE *cover, IMAGE *secret,unsigned int proof_len, char *name);

// OPERATION 4: DECODE_STEGANOGRAPHY
/**
 *
 * @param img
 * @param proof_len
 */
void decode_image(IMAGE *img,unsigned int proof_len, char *name);

// OPERATION 5: ENCODE_TEXT
/**
 *
 * @param filename
 * @return
 */
char *readTextFromFile(char *filename);

/**
 *
 * @param img
 * @param text
 * @param system_key
 */
void putTextInPicture(IMAGE *img, char *text, unsigned int system_key, char *name);

// OPERATION 6: DECODE_TEXT
/**
 *
 * @param img
 * @param textLen
 * @param system_key
 * @return
 */
char *decodeTextFromImage(IMAGE *img,int textLen,unsigned int system_key, char *name);

// OPERATION 7: IMAGE_TO_STRING
/**
 *
 * @param img
 * @param textFileName
 */
 void stringToImage(IMAGE *img, char *textFileName, char *name);

// OPERATION 8: STRING_TO_IMAGE
/**
 *
 * @param img
 */
void imageToString(IMAGE *img);

#endif //HOMEWORK4_LIBRARY_H