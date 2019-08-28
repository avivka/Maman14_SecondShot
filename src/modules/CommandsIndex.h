/* Includes				*/

#include 	"../constants.h"
#include 	"../utils/Error.h"
#include 	<string.h>

/* Defines				*/

#define 	O_OTHER_OPERAND					-1
#ifndef 	ASSEMBLER_COMMANDSINDEX_H
#define 	ASSEMBLER_COMMANDSINDEX_H

/* Enums				*/

/**
 * Enum that holds all the possible commands that our assembler can handle
 */
typedef enum { mov, cmp, add , sub, notCMD, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop, UNKNOWN_COMMAND } COMMANDS;

/* Structures			*/

/**
 * A type that describes a command,
 *  numberOfOperands - describes the number of operands required by this command.
 *  canUseIndexOperand - boolean wether this command can accepts index operator
 */
typedef struct command_descriptor
{
    int numberOfOperands;
    boolean canUseIndexOperand;
    int allowedSrcOperands[4];
    int allowedDestOperands[4];
} CommandDescriptor;

/* Prototypes	*/

/**
 * Init the map of the commands */
void 			initCommandsDescriptors			();

/**
 * Gets the command descriptor for the given command, if not given a command string will return NULL.
 * @param command
 * @return
 */
CommandDescriptor* getCommandDescriptor			(COMMANDS);

/**
 * Converts the given string to one of the COMMANDS Enums, if it do not match, return UNKNOWN_COMMAND.
 * @param commandString - string to check if matches to enum.
 * @return COMMANDS enum
 */
COMMANDS 		commandStringToEnum				(char*);

#endif
