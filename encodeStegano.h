#ifndef HOMEWORK4_ENCODESTEGANO_H
#define HOMEWORK4_ENCODESTEGANO_H

#include "bmp.h"
#include <math.h>
#include <string.h>

/**
 * Method that encodes a secret picture to a cover one.
 *
 * @param cover
 * @param secret
 * @param proof_len
 */
void change_pixels(IMAGE *cover, IMAGE *secret,unsigned int proof_len);

/**
 *  Method that calculates the mask.
 *
 * @param proof_length
 * @return
 */
unsigned char calculate_mask(unsigned int proof_length);

#endif //HOMEWORK4_ENCODESTEGANO_H
