#ifndef HOMEWORK4_GRAYSCALE_H
#define HOMEWORK4_GRAYSCALE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


/**
 * Method that will get a BMP image as a parameter,
 * will transform it to a black and white image and
 * store it as a new image with the name of "grayscaled.bmp"
 *
 * @param img The image that the method will transform
 */
void createGrayscale(IMAGE *img);

#endif //HOMEWORK4_GRAYSCALE_H

