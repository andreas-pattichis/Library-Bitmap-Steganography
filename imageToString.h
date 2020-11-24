#ifndef HOMEWORK4_IMAGETOSTRING_H
#define HOMEWORK4_IMAGETOSTRING_H

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
void imageToString(IMAGE *img);

#endif //HOMEWORK4_IMAGETOSTRING_H