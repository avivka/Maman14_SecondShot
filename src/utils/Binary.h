#ifndef ASSEMBLER_WIERDBINARY_H

#include <stdlib.h>

/**
 * Converts the given int, to a binary digits sets of required size
 * @param in
 * @param count
 * @return
 */
unsigned int* int_to_bin_digit(unsigned int in, int count);
/**
 * Converts a given int to a binary string of required size
 * @param n
 * @param numOfDigits
 * @return
 */
char *decimal_to_binaryString(int n, int numOfDigits);

#define ASSEMBLER_WIERDBINARY_H

#endif
