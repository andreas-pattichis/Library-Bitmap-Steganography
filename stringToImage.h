#ifndef HOMEWORK4_STRINGTOIMAGE_H
#define HOMEWORK4_STRINGTOIMAGE_H

#include "bmp.h"
#include <math.h>
#include <string.h>

/**
 *
 * @param m
 * @param n
 * @return
 */
int getBit(char *m, int n);

/**
 *
 * @param img
 * @param textFile
 */
void stringToImage(IMAGE *img, char *textFile);

#endif //HOMEWORK4_STRINGTOIMAGE_H