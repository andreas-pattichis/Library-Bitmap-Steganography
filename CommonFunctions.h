/**
 *  @file CommonFunctions.h
 *  @brief Class that includes the prototypes for all the functions that are used in multiple operations
 *
 *  @author Costa Christian (ccosta01), Andreas Pattichis (apatti01)
 *  @bug No know bugs.
 */

/* Libraries included */
#include "bmp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * Method that returns the nth bit of a string
 *
 * @param m the string that will be checked
 * @param n the number of the bit that will be returned
 *
 * @return the nth bit
 */
int getBit(char *m, int n);

/**
 *
 * @param n
 * @param system_key
 * @return
 */
int *createPermutationFunction(int n, unsigned int system_key);