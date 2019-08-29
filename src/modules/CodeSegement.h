/* Includes				*/

#include 	"Analyzer.h"
#include 	"Opearnds.h"
#include 	"DataSegment.h"
#include 	"SymbolsTable.h"
#include    "CreateBMC.h"

/* Prototypes	*/

/** returns the current count of command instructions */
int 	    getInstructionsCount						();

/** resets the Code Segment module, re-initialaizing it, usually used when start to work with a new file */
void 		resetCodeSegmentModule		                ();

/**
 * should go over the instruction and increase the Command instructions count based on the given statement
 * @param the statement, which is a sentence that we're about to spilt to words.
 */
void	    increaseCommandInstructionsCountByStatement	(char*);

commandLine addStatementToCodeSegment					(char*);

void 	    initCodeSection								(char*, int);

/**
 * Go through the operands list, and check weather all the operands match the allowed operands defined by the given CMD, print error for any un-allowed operand
 * @param operandsList
 * @param cmd
 */
void 	    validateIfOperandsAreaAllowed				(OperandNode*, COMMANDS);

/**
 * Check if the given operand type is allowed for this command, at this position, errors if not
 * @param operandType the type  to check
 * @param cmd  which command
 * @param operandPosition  at which position
 */
void 	    validateOperandAllowedForCommand			(OperandType, COMMANDS, OperandPosition);

