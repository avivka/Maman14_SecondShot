/* Includes				*/
#ifndef        ASSEMBLER_FILEREADER_H
#define        ASSEMBLER_FILEREADER_H

#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	"../constants.h"
#include 	"TextUtils.h"

/* Defines				*/

/* Function Declaration	*/

int 		check_if_file_exists	 	(char*);
char* 		rename_file					(char *, char*);
int 		open_or_create_file			(FILE**, char*);

/**
 * Keep getting line by line until the end of file.
 * @param file pointer to file.
 * @param nextLineHandler pointer to fucnction that get the next line.
 */
void doWhileFileHaveLines(FILE*, void (*nextLineHandler)(char*));
/*void DoWhileFileHaveLines(char*, void (*nextLineHandler)(char*));*/
#endif
