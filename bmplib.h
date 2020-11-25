/**
 *  @file bmplib.h
 *  @brief Class that includes the prototype of all the functions that are used in the 8 operations.
 *
 *  @author Costa Christian (), Andreas Pattichis (apatti01)
 *  @bug No know bugs.
 */

/* Header file that contains all the methods for all the operations*/
#ifndef HOMEWORK4_LIBRARY_H
#define HOMEWORK4_LIBRARY_H

#define MAX_WORDS 5000

/*libraries included */
#include "CommonFunctions.h"

/* OPERATION 1: LIST */

/**
 * @brief Method that transforms a string of characters to an integer
 *
 * @param arr String that will be transformed
 * @param arrLen The number of the characters
 *
 * @return the integer
 */
int convert_to_anInteger(char *arr, int arrLen);

/**
 * @brief Method that prints all the information that is asked fr the image that is given as a parameter
 *
 * @param img The image that will be explored
 */
void print_information(IMAGE *img);


/* OPERATION 2: GRAYSCALE */

/**
 *  @brief Method that reads a BMP image and transforms it to black and white.
 *  The image is stored as "nameOfTheImage_grayscale.bmp"
 *
 * @param img The image that will be transformed
 * @param name The name of the image
 */
void createGrayscale(IMAGE *img, char *name);


/* OPERATION 3: ENCODE_STEGANOGRAPHY */

/**
 * @brief Calculates and returns the mask of an unsigned integer
 *
 * @param proof_length The unsigned integer
 *
 * @return mask
 */
unsigned char calculate_mask(unsigned int proof_length);

/**
 * @brief Encoding a secret image to the cover image and saving the new image
 * as "new-imageName.bmp"
 *
 * @param cover The cover image
 * @param secret The secret image
 * @param proof_len
 * @param name The name of the image
 */
void change_pixels(IMAGE *cover, IMAGE *secret,unsigned int proof_len, char *name);


/* OPERATION 4: DECODE_STEGANOGRAPHY */

/**
 * @brief Method that recovers the secret image and stores it as "new-new-imageName.bmp"
 *
 * @param img The image that will be processed
 * @param proof_len
 * @param name The name of the image
 */
void decode_image(IMAGE *img,unsigned int proof_len, char *name);


/* OPERATION 5: ENCODE_TEXT */

/**
 * @brief Method that reads and returns the text from the text file that is
 * given as a parameter
 *
 * @param filename The name of the text file
 *
 * @return String of characters
 */
char *readTextFromFile(char *filename);

/**
 * @brief Method that encodes a text to the picture and stores it as
 * "new-imageName"
 *
 * @param img The image that will be processed
 * @param text The text file that will be encoded
 * @param system_key
 * @param name The name of the image
 */
void putTextInPicture(IMAGE *img, char *text, unsigned int system_key, char *name);

/* OPERATION 6: DECODE_TEXT */

/**
 * @brief Recovers the text from the image
 *
 * @param img The image that will be processed
 * @param textLen The length of the text
 * @param system_key
 * @param name The name of the image
 *
 * @return the text
 */
char *decodeTextFromImage(IMAGE *img,int textLen,unsigned int system_key, char *name);


/* OPERATION 7: IMAGE_TO_STRING */

/**
 * @brief Method that creates a BMP image from a text file
 *
 * @param img The image that will give the information of the new image that will be created
 * @param textFileName The name of the text file that will be read
 */
 void stringToImage(IMAGE *img, char *textFileName, char *name);

/* OPERATION 8: STRING_TO_IMAGE */

/**
 * @brief Method that recovers the text from the image and saves it to the text file "Output.txt"
 *
 * @param img The image that will be processed
 */
void imageToString(IMAGE *img);

/**
 *
 * @param text
 * @return
 */
int calculate_length_of_String(char *text);

#endif //HOMEWORK4_LIBRARY_H