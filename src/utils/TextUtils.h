/* Includes				*/

#include 	<stdlib.h>
#include 	<stdio.h>
#include 	<string.h>
#include 	<ctype.h>
#include 	"Error.h"
#include 	"../constants.h"

/* Defines				*/

#ifndef 	ASSEMBLER_TEXTUTILS_H
#define 	ASSEMBLER_TEXTUTILS_H

/**
 * Gets an input, returns wether it contains the char
 * @param input  the input to check
 * @return 0 if do not contains comma, 1 the input contains comma
 */
int 		isContainsComma			(char*);

/**
 * Gets an input, returns wether it contains a given character
 * @param input the input to check
 * @param charToTest which character to look for
 * @return 1 if contains, 0 if not
 */
int 		isContainsChar			(char*, char);

/**
 * Getting a word, and character to test, returns if 1 the last chartaer of the give word, matches the charToTest. or 0 if not.
 * @param word -  a word to check against
 * @param charToTest - the char to check if it the last character of the given word
 * @return 1 if last character matches, 0 if not
 */
int 		isWordEndsWithChar		(char*, char);

/**
 * Getting a word, and character to test, returns if 1 the first character of the give word, matches the charToTest. or 0 if not.
 * @param word -  a word to check against
 * @param charToTest - - the char to check if it the first character of the given word
 * @return 1 if first character matches, 0 if not
 */
int 		isWordStartsWithChar	(char*, char);

/**
 * Returns the last char of a given word
 * @param word
 * @return
 */
char 		getLastChar				(char*);

/**
 * Check if the two given chars are the same
 * @param c
 * @param toCompare
 * @return true if they are the same, false if not
 */
boolean 	isCharsEqual			(char, char);

/**
 * Trims leading and trailing spaces from the str
 * @param str
 * @return
 */
char* 		trimwhitespace			(char*);

/**
 * Returns a new string from the given string, between the from index until the to index.
 * @param string
 * @param from - index from which to start the substring
 * @param to - index to end the substring
 * @return
 */
char* 		substringFromTo			(char*, int, int);

/** check if the given string reprents a number, if not throws an error */
void 		validateStringIsNumber	(char*);

void 		removeExtraSpaces		(char*);

/**
 * Concat s1 and s2 to a new string of both combined
 * @param s1
 * @param s2
 * @return the new combined string of s1 & s2
 */
char* 		concat					(const char*, const char*);

char* 		is_extention_exists		(char*, char*);

#endif
