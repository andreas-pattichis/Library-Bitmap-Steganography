#include "bmp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
 * @param n
 * @param system_key
 * @return
 */
int *createPermutationFunction(int n, unsigned int system_key);