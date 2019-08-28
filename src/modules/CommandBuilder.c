#include "CommandBuilder.h"
/*
CommandStatement 	buildCommandStatement		(OperandType srcOperandType, OperandType destOperandType, COMMANDS commandOpCode, STATEMENT_ENCODING_TYPE encodingType, OperandNode* indexOperandsList)
{
    unsigned int* 		srcOperand;
    unsigned int* 		destOperand;
    unsigned int* 		commandCode;
    unsigned int* 		encodingTypeValue;

    CommandStatement* 	command;
    
    command = (CommandStatement*) malloc(sizeof(CommandStatement));
    errorIfMallocFailed(command, "when trying to allocate memory for command.");

    srcOperand 			= int_to_bin_digit((unsigned int) srcOperandType, 2);
    destOperand 		= int_to_bin_digit((unsigned int) destOperandType, 2);
    commandCode 		= int_to_bin_digit((unsigned int) commandOpCode, 4);
    encodingTypeValue 	= int_to_bin_digit((unsigned int) encodingType, 2);

    command->encoding_type_1 = encodingTypeValue[0];
    command->encoding_type_2 = encodingTypeValue[1];

    command->destination_operand_1 = destOperandType == NO_OPERAND ? 0 : destOperand[0];
    command->destination_operand_2 = destOperandType == NO_OPERAND ? 0 : destOperand[1];

    command->source_operand_1 = srcOperandType == NO_OPERAND ? 0 : srcOperand[0];
    command->source_operand_2 = srcOperandType == NO_OPERAND  ? 0 : srcOperand[1];

    command->op_code_1 = commandCode[0];
    command->op_code_2 = commandCode[1];
    command->op_code_3 = commandCode[2];
    command->op_code_4 = commandCode[3];

    command->not_in_use_1 = 0;
    command->not_in_use_2 = 0;
    command->not_in_use_3 = 0;
    command->not_in_use_4 = 0;

    return  *command;
}
*/
/*
char* 				getCommandBinaryString		(CommandStatement* cmd)
{
    char* 		string 		= "";

    string = malloc(14 * sizeof(char));
    errorIfMallocFailed(string, "when trying to allocate memory to string of bmc.");

    sprintf(string, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                     cmd->not_in_use_1,
                     cmd->not_in_use_2,
                     cmd->not_in_use_3,
                     cmd->not_in_use_4,
                     cmd->op_code_1,
                     cmd->op_code_2,
                     cmd->op_code_3,
                     cmd->op_code_4,
                     cmd->source_operand_1,
                     cmd->source_operand_2,
                     cmd->destination_operand_1,
                     cmd->destination_operand_2,
                     cmd->encoding_type_1,
                     cmd->encoding_type_2
    );
    
    return  string;
}*/
