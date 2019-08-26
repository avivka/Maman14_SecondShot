#ifndef ASSEMBLER_COMMANDBUILDER_H

#include "../utils/Binary.h"
#include "Opearnds.h"

typedef struct {
    unsigned int encoding_type_1: 1;
    unsigned int encoding_type_2: 1;
    unsigned int destination_operand_1: 1;
    unsigned int destination_operand_2: 1;
    unsigned int source_operand_1: 1;
    unsigned int source_operand_2: 1;
    unsigned int op_code_1: 1;
    unsigned int op_code_2: 1;
    unsigned int op_code_3: 1;
    unsigned int op_code_4: 1;
    unsigned int not_in_use_3: 1;
    unsigned int not_in_use_4: 1;
    unsigned int not_in_use_1: 1;
    unsigned int not_in_use_2: 1;
} CommandStatement;



typedef  enum {
    ABSOLUTE,
    EXTERNAL,
    RELOCATEABLE
} STATEMENT_ENCODING_TYPE;

CommandStatement buildCommandStatement(OperandType srcOperandType, OperandType destOperandType, COMMANDS commandOpCode, STATEMENT_ENCODING_TYPE encodingType, OperandNode* indexOperandsList);

char* getCommandBinaryString(CommandStatement *cmd);

#define ASSEMBLER_COMMANDBUILDER_H

#endif
