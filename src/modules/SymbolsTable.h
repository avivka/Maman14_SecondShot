#ifndef ASSEMBLER_SYMBOLSTABLE_H
#define ASSEMBLER_SYMBOLSTABLE_H

#include <stdlib.h>
#include <string.h>
#include "Analyzer.h"
#include "../constants.h"
#include "../utils/Error.h"

/** returns the current data instructions count **/
int getDataInstructionsCount();

/**
 * Increase the DataInstructionsCount by one.
 */
void increaseDataInstructionsCount();

typedef enum
{
  	macro,
	code,
	dat,
	ext
} labelFeature;

typedef struct symbol_struct{
    char* 					label;
    labelFeature			feature;
    int 					address;
    struct symbol_struct*	next;
} Symbol;


/**
 * Builds a new Symbol object
 * @param 	label - the label of the new symbol
 * @param 	feature - the source of the symbol, macro / code / data / external.
 * @param 	address - the memory address where the label is stored
 * @return 	pointer to the newly created Symbol
 */
Symbol* buildSymbol(char* label, labelFeature feature, int address);

/**
 * Adds a new symbol to the symbols table
 * @param newSymbol
 */
void addSymbolToTable(Symbol *newSymbol);

/**
 * @return the head of the SymbolTable
 */
Symbol* getSymbolsTableHead();


/**
 * @return the tail of the SymbolTable
 */
Symbol* getSymbolsTableTail();

/**
 * Searches if the current table has a symbol wih the request label
 * @param label
 * @return if found returns a pointer to the symbol containing the requested label, otherwise returns NULL
 */
Symbol* searchForSymbolByLabel(char* label);

int getSymbolAddress(char *symbolLabel);

/**
 * resets the SymbolsTable module, re-init it,
 *  frees all the table memory and rests data instruction counter.
 *   usually used when starting to work with a new file
 */
void resetSymbolsModulesModule();

int	printSymbolTable ();

#endif

