#include "CommandBuilder.h"


CommandStatement buildCommandStatement(OperandType srcOperandType, OperandType destOperandType, COMMANDS commandOpCode, STATEMENT_ENCODING_TYPE encodingType, OperandNode* jumpOperandsList){
    unsigned int *srcOperand;
    unsigned int *destOperand;
    unsigned int *commandCode;
    unsigned int *encodingTypeValue;

    CommandStatement *command;
    command = (CommandStatement*) malloc(sizeof(CommandStatement));

    srcOperand = int_to_bin_digit((unsigned int) srcOperandType
            , 2);
    destOperand = int_to_bin_digit((unsigned int) destOperandType, 2);
    commandCode = int_to_bin_digit((unsigned int) commandOpCode, 4);
    encodingTypeValue = int_to_bin_digit((unsigned int) encodingType, 2);

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

    if(jumpOperandsList == NULL){
        command->jump_param_1_1 = 0;
        command->jump_param_1_2 = 0;
        command->jump_param_2_1 = 0;
        command->jump_param_2_2 = 0;
    } else {
        OperandType jumpParam1Type;
        OperandType jumpParam2Type;
        unsigned  int* jumpParam1Value;
        unsigned  int* jumpParam2Value;

        jumpParam1Type = jumpOperandsList->type;
        jumpParam2Type = jumpOperandsList->next->type;

        jumpParam1Value = int_to_bin_digit((unsigned int) jumpParam1Type, 2);
        jumpParam2Value = int_to_bin_digit((unsigned int) jumpParam2Type, 2);

        command->jump_param_1_1 = jumpParam1Value[0];
        command->jump_param_1_2 = jumpParam1Value[1];
        command->jump_param_2_1 = jumpParam2Value[0];
        command->jump_param_2_2 = jumpParam2Value[1];
    }
    return  *command;
}

char* getCommandBinaryString(CommandStatement *cmd){
    char *string;
    string = malloc(14 * sizeof(char));
    sprintf(string, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                     cmd->jump_param_1_1,/**bit 13:*/ /*TODO: should not be in use*/
                     cmd->jump_param_1_2,/**bit 12:*/ /*TODO: should not be in use*/
                     cmd->jump_param_2_1,/**bit 11:*/ /*TODO: should not be in use*/
                     cmd->jump_param_2_2,/**bit 10:*/ /*TODO: should not be in use*/
                     cmd->op_code_1,/**bit 9: op_code*/
                     cmd->op_code_2,/**bit 8: op_code*/
                     cmd->op_code_3,/**bit 7: op_code*/
                     cmd->op_code_4,/**bit 6: op_code*/
                     cmd->source_operand_1,/**bit 5: source operand addressing method code*/
                     cmd->source_operand_2,/**bit 4: source operand addressing method code*/
                     cmd->destination_operand_1,/**bit 3: destination operand addressing method code*/
                     cmd->destination_operand_2,/**bit 2: destination operand addressing method code*/
                     cmd->encoding_type_1,/**bit 1: A,R,E code*/
                     cmd->encoding_type_2 /**bit 0: A,R,E code*/
    );
    return  string;
}
