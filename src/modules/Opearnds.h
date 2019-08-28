/* Includes 		*/

#include <stdlib.h>
#include <string.h>
#include "../utils/TextUtils.h"
#include "../utils/Error.h"
#include "../constants.h"
#include "Analyzer.h"
#include "SymbolsTable.h"
#include "CommandsIndex.h"

/* Definitions		*/

#ifndef ASSEMBLER_OPEARNDS_H
#define ASSEMBLER_OPEARNDS_H

/* Enums			*/

typedef enum
{
    SRC_OPERAND,
    TARGET_OPERAND
} OperandPosition;

/* Structures		*/

/**
 * OperandNode defines an operand node type, contains the type and the value of the current operand, references to the next operand.
 */
typedef struct operand_node {
    OperandType type;
    char *value;
    struct operand_node *next;
} OperandNode;

typedef struct
{
    COMMANDS            command;
    OperandNode			srcoperand;
    OperandNode			desoperand;
} commandLine;

/* Prototypes 	*/

/**
 * Gets a string pointer, pointing to the beging of operands section of a string
 * @param operandsStartPtr - pointing to the beginning of operands string
 * @param statementType - the type of the statement that used these operands
 * @return a pointer to a list of operands that the string contained
 */
OperandNode* 	getOperandsListOfStatement	(char*, STATEMENT_TYPE, char*);

/**
 * Gets an operand list pointer, returns the total amount of operands in the list.
 * @param operandsList
 * @return total number of operands in the list.
 */
int 			countNumberOfOpearnds		(OperandNode*);

/**
 * Reads a value of INDEX operand, and returns a list of the 2 operands that the index operand points to
 * @param indexOperandString - string
 * @return list of operands
 */
OperandNode* 	getOperandListOfIndexOperand(char*);

char* 			getOperandFromDefine 		(char*, int);

#endif
