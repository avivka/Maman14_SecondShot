#include "CodeSegement.h"

void addToCodeSection(CommandStatement cmd);
void addOperandValueToCodeSection(OperandNode* operand, OperandPosition operandPos);
void addOperandsValuesToCodeSection(OperandNode* operandsList);
/**
 * Go through the operands list, and check wether all the operands match the allowed operands defined by the given CMD, print error for any unallowed operand
 * @param operandsList
 * @param cmd
 */
void validateIfOperandsAreaAllowed(OperandNode* operandsList, COMMANDS cmd);
/**
 * Check if the given operand type is allowed for this command, at this position, errors if not
 * @param operandType the type  to check
 * @param cmd  which command
 * @param operandPosition  at which positon
 */

void validateOperandAllowedForCommand(OperandType operandType, COMMANDS cmd, OperandPosition operandPosition);

/** Instruction counter */
static  int IC = 0;
static char** codeSection;

int getInstructionsCount(){
    return  IC;
}

char** getCodeSection(){
    return  codeSection;
}

void resetCodeSegmentModule(){
    IC = 0; /* resets the instructions count */
}

void initCodeSection(){
    codeSection = (char**)malloc(IC * sizeof(char*));
    printf("this is the IC size:%d\n", IC);
    errorIfMallocFailed(codeSection, "when tring to allocate memory for code section check.");
    
    IC = 0;
}

void increaseCommandInstructionsCountByStatement(char* statement){
    char *label = extractLabel(statement);
    Symbol* newSymbol = NULL;
    OperandNode *operandsList = NULL;
    OperandNode *indexSrcOperand = NULL;
    OperandNode *indexDesOperand = NULL;
    int operandsCount = 0;

    /** if statment has a label, add it to the symbols table */
    if(label != NULL){
		printf("check ic = %d %s \n", getInstructionsCount(), statement);
		
        newSymbol = buildSymbol(label, code, getInstructionsCount() + MEMOERY_START_ADDRESS);
        addSymbolToTable(newSymbol);
    }
	printf("!!!!!!!!!!!!!!!!!!!check all good!!!!!!!!!!!!!!!!! \n");
    operandsList = getOperandsListOfStatement(statement, COMMAND_STATEMENT, label);
    operandsCount = countNumberOfOpearnds(operandsList);
    /** first increase IC by one for the command it self */
    IC++;
    switch (operandsCount){
        case 2:
            if(operandsList->type == REGISTER_OPERAND && operandsList->next->type == REGISTER_OPERAND)
            {
                /** if both operands, are of register type, increase only by one for both operands */
                IC++;
            }
            
            else if((!(operandsList->next->type == INDEX_OPERAND)) && (!(operandsList->type == INDEX_OPERAND)))
            {
				/** increase by 1 for each operand */
				printf("check both are not index \n");
				
				IC += 2;
            } 
            
            else if (operandsList == NULL)
            {
				printf("check operand list = null \n");
			}
			
			else
            {
				if(operandsList->type == INDEX_OPERAND)
				{
					printf("check got here, %s \n", operandsList->value);
                    indexSrcOperand = getOperandListOfIndexOperand(operandsList->value);
                    
                    if(indexSrcOperand->type == INDEX_OPERAND)
                    {
                        ERROR_PROGRAM(("index operands cant contain other index operand"));
					}
					
                    IC += 2;
					
				}
					
				if(operandsList->next->type == INDEX_OPERAND)
				{
					printf("\n check got here, %s %d \n", operandsList->next->value, operandsList->next->type);
                    indexDesOperand = getOperandListOfIndexOperand(operandsList->next->value);       
                    if(indexDesOperand->type == INDEX_OPERAND)
                    {
                        ERROR_PROGRAM(("index operands cant contain other index operand"));
					}
                    
                    IC += 2;
				}
				
				if(((operandsList->type == INDEX_OPERAND) && (operandsList->next->type != INDEX_OPERAND)) || ((operandsList->type != INDEX_OPERAND) && (operandsList->next->type == INDEX_OPERAND)))
				{
					IC += 1;
				}
			}
			 
            break;
            
        case 1:
            if(operandsList->type == INDEX_OPERAND){
				printf("check got here, %s \n", operandsList->value);
                    indexDesOperand = getOperandListOfIndexOperand(operandsList->value);
                    if(indexDesOperand->type == INDEX_OPERAND || indexDesOperand->next->type == INDEX_OPERAND){
                        ERROR_PROGRAM(("index operands cant contain other index operand"));
                    } else if (indexDesOperand->type == REGISTER_OPERAND || indexDesOperand->next->type == REGISTER_OPERAND){
                        /** increase by 1 for the index label, and by another one for both arguments as they fit one word */
                        ERROR_PROGRAM(("index operands cant contain register operand"));
                    } else{
                        /** increase by one for index label value, and by one for each of the two operands */
                        IC += 2;
                    }
            } else{
                /** just increase by one */
                IC++;
            }
            break;
        case 0:
            /** nothing to do */
            break;
        default:
            ERROR_PROGRAM(("invalid number of operands for a command statement, got %d, expected to be between 0 to 2", operandsCount));
            break;
    }
    
    printf("check ic = %d \n", IC);

}

void addStatementToCodeSegment(char* statement){
    OperandNode *operandsList;
    CommandDescriptor *descriptor;
    CommandStatement command;
    OperandNode* indexList;
    char* label;
    COMMANDS commandEnum;
    int operandsCount;
    /** get rid of unneeded white spaces */
    removeExtraSpaces(statement);
    trimwhitespace(statement);
    label = extractLabel(statement);
    operandsList = getOperandsListOfStatement(statement, COMMAND_STATEMENT, label);
    operandsCount = countNumberOfOpearnds(operandsList);
    commandEnum = getCommandOfStatement(statement);
    descriptor = getCommandDescriptor(commandEnum);
    if(descriptor == NULL){
        ERROR_PROGRAM(("unknown command"));
            return;
    }

    if(operandsCount != descriptor->numberOfOperands){
        ERROR_PROGRAM(("invalid number of operands got %d, expected %d", operandsCount, descriptor->numberOfOperands));
    }

    validateIfOperandsAreaAllowed(operandsList, commandEnum);

    switch (operandsCount){
        case 0:
            command = buildCommandStatement(NO_OPERAND, NO_OPERAND, commandEnum, ABSOLUTE, NULL);
            addToCodeSection(command);
            break;
        case 1:
            indexList = NULL;
            if(operandsList->type == INDEX_OPERAND){
                indexList = getOperandListOfIndexOperand(operandsList->value);
            }
            command = buildCommandStatement(NO_OPERAND, operandsList->type, commandEnum, ABSOLUTE, indexList);

            break;
        case 2:
            command = buildCommandStatement(operandsList->type, operandsList->next->type, commandEnum, ABSOLUTE, NULL);
            break;
    }

    addToCodeSection(command);
    addOperandsValuesToCodeSection(operandsList);
}

void addToCodeSection(CommandStatement cmd){
    codeSection[IC] = getCommandBinaryString(&cmd);
    IC++;
}

void addOperandsValuesToCodeSection(OperandNode* operandsList){
    STATEMENT_ENCODING_TYPE encoding_type;

    /** nothing to do if no operands */
    if(operandsList == NULL)
        return;

    /** two operands check*/
    if(operandsList->next != NULL){
        /** if both operands are of type of register, we can combine them to a single word */
        if(operandsList->next->type == REGISTER_OPERAND && operandsList->type == REGISTER_OPERAND){
            char *registerOneValue;
            char *registerTwoValue;

            registerOneValue = decimal_to_binaryString(getRegisterNumberOfOperand(operandsList), COMMAND_REGISTER_LENGTH);
            registerTwoValue = decimal_to_binaryString(getRegisterNumberOfOperand(operandsList->next), COMMAND_REGISTER_LENGTH);
            /** registers are absolute encoded */
            encoding_type = ABSOLUTE;
            codeSection[IC] = concat(concat(registerOneValue, registerTwoValue),decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));
            IC++;
            return;
        }

        /** two operands different types, add each of them, first operand is treated as src operand, second as the target operand */
        addOperandValueToCodeSection(operandsList, SRC_OPERAND);
        addOperandValueToCodeSection(operandsList->next, TARGET_OPERAND);
        return;
    }

    /** if we are here we are handling a single operand add it value. single values are treated as target operands */
    addOperandValueToCodeSection(operandsList, TARGET_OPERAND);
}

void addOperandValueToCodeSection(OperandNode* operand, OperandPosition position){
    STATEMENT_ENCODING_TYPE encoding_type;
    Symbol* symbol;
    char *value;
    if(operand->type == DIRECT_VALUE_OPERAND){
        /** direct values do not need to be reallocted they are absolute */
        encoding_type = ABSOLUTE;
        /** direct value of command statements, are gaurnteed to be numbers we can use atoi safely */
        value = decimal_to_binaryString(atoi(operand->value), COMMAND_VALUE_LENGTH);
    } else if(operand->type == REGISTER_OPERAND){
        encoding_type = ABSOLUTE;
        if(position == SRC_OPERAND){
            /** src register operands should encode the binary value of register number, and padd the value with 6 zeros */
            value = concat(decimal_to_binaryString(getRegisterNumberOfOperand(operand), COMMAND_REGISTER_LENGTH), decimal_to_binaryString(0, COMMAND_REGISTER_LENGTH));
        } else {
            /** target register operands should start wuth 6 zeros, and then the binary value of the register value */
            value = concat(decimal_to_binaryString(0, COMMAND_REGISTER_LENGTH), decimal_to_binaryString(getRegisterNumberOfOperand(operand), COMMAND_REGISTER_LENGTH));
        }
    } else if(operand->type == INDEX_OPERAND){
        char *indexLabel;
        int indexLabelAddress;
        OperandNode *indexOperands;
        indexOperands = getOperandListOfIndexOperand(operand->value);
        indexLabel = extractIndexOperandLabel(operand->value);
		
        /** find the index label in the symbols table */
        printf("check %s", indexLabel);
        
        if(!(isnumber(indexLabel)))
			symbol = searchForSymbolByLabel(indexLabel);
        if(symbol == NULL){
            ERROR_PROGRAM(("Unknown symbol %s in index statement", indexLabel));
            return;
        }
        /** if it an external symbol, we encode a different ARE bits, as it  external not relocatable */
        if(symbol->feature == ext){
            encoding_type = EXTERNAL;
            /** add the external usage to the external symbols usage list*/
            addExternalStatementUsage(symbol->label, IC + MEMOERY_START_ADDRESS);
        } else {
            encoding_type = RELOCATEABLE;
        }
        indexLabelAddress = symbol->address;
        /** add the index label first */
        codeSection[IC] = concat(decimal_to_binaryString(indexLabelAddress, COMMAND_VALUE_LENGTH), decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));
        IC++;
        /** add the index operands */
        addOperandsValuesToCodeSection(indexOperands);
        return;
    } else{  /** then its a label operand */
        Symbol* symbol;
        /** find the label in the symbols table */
        if(!(isnumber(operand->value)))
        {
			symbol = searchForSymbolByLabel(operand->value);
		
			if(symbol == NULL){
				ERROR_PROGRAM(("Unknown symbol %s", operand->value));
				return;
			}
        
        /** if it an external symbol, we encode a different ARE bits, as it  external not relocatable */
			if(symbol->feature == ext){
				encoding_type = EXTERNAL;
				addExternalStatementUsage(symbol->label, IC + MEMOERY_START_ADDRESS);
			} else {
				encoding_type = RELOCATEABLE;
			}
		}
		value = decimal_to_binaryString(symbol->address, COMMAND_VALUE_LENGTH);
    }

    /** combine statement and the encoding type bits */
    codeSection[IC] = concat(value, decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));
    IC++;
}

void validateIfOperandsAreaAllowed(OperandNode* operandsList, COMMANDS cmd){
    int operandsCount;
    operandsCount = countNumberOfOpearnds(operandsList);
    switch (operandsCount){
        case 1:
            validateOperandAllowedForCommand(operandsList->type, cmd, TARGET_OPERAND);
            break;
        case 2:
            validateOperandAllowedForCommand(operandsList->type, cmd, SRC_OPERAND);
            validateOperandAllowedForCommand(operandsList->next->type, cmd, TARGET_OPERAND);
            break;
        default:
            return;
    }
}

void validateOperandAllowedForCommand(OperandType operandType, COMMANDS cmd, OperandPosition operandPosition){
    CommandDescriptor *descriptor = NULL;
    boolean result = FALSE;
    descriptor = getCommandDescriptor(cmd);
    /** zero operands commands can't have any operand */
    if(descriptor->numberOfOperands == 0)
    return;
    /** single operand statements can only have Destination operands */
    if((descriptor->numberOfOperands == 1) && (operandPosition == TARGET_OPERAND)){
        return;
    }

    switch (operandPosition){
        case SRC_OPERAND:
            if((descriptor->allowedSrcOperands[0] == operandType) || (descriptor->allowedSrcOperands[1] == operandType) || (descriptor->allowedSrcOperands[2] == operandType) || (descriptor->allowedSrcOperands[3] == operandType))
                result = TRUE;
            break;
        case TARGET_OPERAND:
            if((descriptor->allowedDestOperands[0] == operandType) || (descriptor->allowedDestOperands[1] == operandType) || (descriptor->allowedDestOperands[2] == operandType) || (descriptor->allowedDestOperands[3] == operandType))
                result = TRUE;
            break;
    }

    if(result == FALSE){
        ERROR_PROGRAM(("invalid operator type for command"));
    }
}
