/* Includes				*/

#include 	"Analyzer.h"
#include 	"Opearnds.h"
#include 	"DataSegment.h"
#include 	"SymbolsTable.h"
#include 	"CommandBuilder.h"

/* Defines				*/

#define 	COMMAND_VALUE_LENGTH 			12
#define 	COMMAND_ARE_BITS_LENGTH			2
#define 	COMMAND_REGISTER_LENGTH			6

/* Function Declaration	*/

/** returns the current count of command instructions */
int 	getInstructionsCount						();

/** returns pointer to the code section array */
char** 	getCodeSection								();

/**
 * should go over the instruction and increase the Command instructions count based on the given statment
 */
void	increaseCommandInstructionsCountByStatement	(char*);

/** resets the Code Segment module, reintailzaing it, usually used when start to work with a new file */
void 	resetCodeSegmentModule						();

void 	addStatementToCodeSegment					(char*);
	
void 	initCodeSection								();

void 	addToCodeSection							(CommandStatement);

void 	addOperandValueToCodeSection				(OperandNode*, OperandPosition);

void 	addOperandsValuesToCodeSection				(OperandNode*);

/**
 * Go through the operands list, and check wether all the operands match the allowed operands defined by the given CMD, print error for any unallowed operand
 * @param operandsList
 * @param cmd
 */
void 	validateIfOperandsAreaAllowed				(OperandNode*, COMMANDS);

/**
 * Check if the given operand type is allowed for this command, at this position, errors if not
 * @param operandType the type  to check
 * @param cmd  which command
 * @param operandPosition  at which positon
 */
void 	validateOperandAllowedForCommand			(OperandType, COMMANDS, OperandPosition);

#endif


