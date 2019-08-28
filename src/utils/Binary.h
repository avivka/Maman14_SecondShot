/* Includes				*/
#ifndef        ASSEMBLER_WIERDBINARY_H

#include 	<stdlib.h>
#include 	<stdio.h>
#include 	"Error.h"
#include 	"FileReader.h"

/* Defines				*/

#define 	maxNumDecimalAddress 				1000
#define		char_to_ascii						48
#define 	NUM_OF_ACTIVE_BITS 					14

/**
 * Converts the given int, to a binary digits sets of required size
 * @param in
 * @param count
 * @return
 */
unsigned int* 	int_to_bin_digit							(unsigned int, int);

/**
 * Converts a given int to a binary string of required size
 * @param n
 * @param numOfDigits
 * @return
 */
 
char 			to_4_base_data				(char, char);
char* 			decimal_to_binaryString		(int, int);
/*int				printSignToFileData			(char*, FILE*);*/
int	 			data_from_binary_machine_code_to_fourth_base 	(char*, int*, FILE*);

#define ASSEMBLER_WIERDBINARY_H

#endif

