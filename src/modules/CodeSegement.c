#include "CodeSegement.h"

/* Static Data Members	*/

/** Instruction counter */
static  int 		IC 				= 0;
static char** 		codeSection;

int 		getInstructionsCount		()
{
    return  IC;
}

char** 		getCodeSection				()
{
    return  codeSection;
}

void 		resetCodeSegmentModule		()
{
    IC = 0; /* resets the instructions count */
}

void 		initCodeSection				()
{
    codeSection = (char**)malloc(IC * sizeof(char*));
    printf("this is the IC size:%d\n", IC);
    errorIfMallocFailed(codeSection, "when tring to allocate memory for code section check.");
    
    IC = 0;
}

void 		increaseCommandInstructionsCountByStatement	(char* statement)
{
    char* 			label 			= extractLabel(statement);
    Symbol* 		newSymbol 		= NULL;
    OperandNode* 	operandsList	= NULL;
    OperandNode* 	indexSrcOperand = NULL;
    OperandNode* 	indexDesOperand = NULL;
    int 			operandsCount 	= 0;

    /** if statment has a label, add it to the symbols table */
    if(label != NULL)
    {		
        newSymbol = buildSymbol(label, code, getInstructionsCount() + MEMOERY_START_ADDRESS);
     
        addSymbolToTable(newSymbol);
    }
    
    operandsList = getOperandsListOfStatement(statement, COMMAND_STATEMENT, label);
   
    operandsCount = countNumberOfOpearnds(operandsList);
   
    /** first increase IC by one for the command it self */
    IC++;
   
    switch (operandsCount)
    {
        case 2:
            if(operandsList->type == REGISTER_OPERAND && operandsList->next->type == REGISTER_OPERAND)
            {
                /** if both operands, are of register type, increase only by one for both operands */
                IC++;
            }
            
            else if((!(operandsList->next->type == INDEX_OPERAND)) && (!(operandsList->type == INDEX_OPERAND)))
            {
				/** increase by 1 for each operand */				
				IC += 2;
            } 
            
            else if (operandsList != NULL)
            {
				if(operandsList->type == INDEX_OPERAND)
				{
                    indexSrcOperand = getOperandListOfIndexOperand(operandsList->value);
                    
                    if(indexSrcOperand->type == INDEX_OPERAND)
                    {
                        ERROR_PROGRAM(("index operands cant contain other index operand"));
					}
					
                    IC += 2;
					
				}
					
				if(operandsList->next->type == INDEX_OPERAND)
				{
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
            if(operandsList->type == INDEX_OPERAND)
            {
				indexDesOperand = getOperandListOfIndexOperand(operandsList->value);
				
				if(indexDesOperand->type == INDEX_OPERAND || indexDesOperand->next->type == INDEX_OPERAND)
				{
					ERROR_PROGRAM(("index operands cant contain other index operand"));
				}
				
				else if (indexDesOperand->type == REGISTER_OPERAND || indexDesOperand->next->type == REGISTER_OPERAND)
				{
					/** increase by 1 for the index label, and by another one for both arguments as they fit one word */
					ERROR_PROGRAM(("index operands cant contain register operand"));
				}
				
				else
				{
					/** increae by one for index label value, and by one for each of the two operands */
					IC += 2;
				}
				
            }
            else
            {
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
}

commandLine addStatementToCodeSegment	(char* statement)
{
	char* 				label					= "";
    int 				operandsCount			= 0;
    OperandNode* 		operandsSrcList			= NULL;
    OperandNode* 		operandsDesList			= NULL;
    CommandDescriptor*	descriptor				= NULL;
    CommandStatement 	command;
    COMMANDS 			commandEnum;
    commandLine         newLine;

    /** get rid of unneeded white spaces */
    removeExtraSpaces(statement);
    
    trimwhitespace(statement);
    
    label = extractLabel(statement);

    operandsSrcList = getOperandsListOfStatement(statement, COMMAND_STATEMENT, label);

    if(operandsSrcList ->next == NULL)
    {
        operandsDesList = operandsSrcList;

        operandsSrcList = NULL;
    }

    else
    {
        operandsDesList = operandsSrcList ->next;

        operandsSrcList->next = NULL;
    }

    operandsCount = countNumberOfOpearnds(operandsSrcList);
    
    commandEnum = getCommandOfStatement(statement);
    
    descriptor = getCommandDescriptor(commandEnum);
    
    if(descriptor == NULL)
    {
        ERROR_PROGRAM(("unknown command"));
    
            return;
    }

    /** initialaize line in order to handle command coding with CreateBMC functionalities*/

    newLine.command = commandEnum;
    newLine.srcoperand = *operandsSrcList;
    newLine.desoperand = *operandsDesList;

    if(operandsCount != descriptor->numberOfOperands)
    {
        ERROR_PROGRAM(("invalid number of operands got %d, expected %d", operandsCount, descriptor->numberOfOperands));
    }

    /*
    validateIfOperandsAreaAllowed(operandsList, commandEnum);

    switch (operandsCount)
    {    
        case 0:
            command = buildCommandStatement(NO_OPERAND, NO_OPERAND, commandEnum, ABSOLUTE, NULL);
     
            addToCodeSection(command);
     
            break;
     
        case 1:
            command = buildCommandStatement(NO_OPERAND, operandsList->type, commandEnum, ABSOLUTE, NULL);

            break;
        
        case 2:
            command = buildCommandStatement(operandsList->type, operandsList->next->type, commandEnum, ABSOLUTE, NULL);
        
            break;
    }

    addToCodeSection(command);
    
    addOperandsValuesToCodeSection(operandsList);
    */

    return newLine;
}

void 		addToCodeSection			(CommandStatement cmd)
{
    codeSection[IC] = getCommandBinaryString(&cmd);

    IC++;
}

void 		addOperandsValuesToCodeSection	(OperandNode* operandsList)
{
	printf("check add \n");
	
    STATEMENT_ENCODING_TYPE encoding_type;

    /** nothing to do if no operands */
    if(operandsList == NULL)
    {
		printf("check return null \n");
		
        return;
	}

    /** two operands check*/
    if(operandsList->next != NULL)
    {
        /** if both operands are of type of register, we can combine them to a single word */
        if(operandsList->next->type == REGISTER_OPERAND && operandsList->type == REGISTER_OPERAND)
        {
			printf("check 2 registers");
			
            char *registerOneValue;
            char *registerTwoValue;

            registerOneValue = decimal_to_binaryString(getRegisterNumberOfOperand(operandsList), COMMAND_REGISTER_LENGTH);
            printf("check registerOneValue:%s\n", registerOneValue);
            registerTwoValue = decimal_to_binaryString(getRegisterNumberOfOperand(operandsList->next), COMMAND_REGISTER_LENGTH);
            printf("check registerTwoValue:%s\n", registerTwoValue);


            /** registers are absolute encoded */
            encoding_type = ABSOLUTE;
        
            codeSection[IC] = concat(concat(registerOneValue, registerTwoValue),decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));

            printf("check codeSection[IC]: %s\n", codeSection[IC]);

            IC++;
        
            return;
        }

		printf("check add to code section \n");
		
        /** two operands different types, add each of them, first operand is treated as src operand, second as the target operand */
        addOperandValueToCodeSection(operandsList, SRC_OPERAND);
        printf("check operandsList on addOperandsValuesToCodeSection: %s\n", operandsList->value);
        addOperandValueToCodeSection(operandsList->next, TARGET_OPERAND);
        printf("check operandsList (next) on addOperandsValuesToCodeSection: %s\n", operandsList->next->value);

        return;
    }

	printf(" check single operand %s \n", operandsList->value);
	
    /** if we are here we are handling a single operand add it value. single values are treated as target operands */
    addOperandValueToCodeSection(operandsList, TARGET_OPERAND);
}

void 		addOperandValueToCodeSection	(OperandNode* operand, OperandPosition position)
{
	printf("check add 2\n");
	
    Symbol* 				symbol			= NULL;
    char* 					value			= "";
    STATEMENT_ENCODING_TYPE encoding_type;

    printf("check %d \n",operand->type);

    if(operand->type == DIRECT_VALUE_OPERAND)
    { /** addressing method type 1*/

        printf("check direct \n");
        /** direct values  do not need to be reallocated they are absolute */
        encoding_type = ABSOLUTE;
        /** direct value of command statements may be numbers or macro, therefore we need to check that the value exists and convert it to number */
        if (!isnumber(operand->value) && validateLabel(operand->value) && searchForSymbolByLabel(operand->value)->feature == macro)
        {
            value = decimal_to_binaryString(getSymbolAddress(operand->value), COMMAND_VALUE_LENGTH);
        }
        else
        {
            value = decimal_to_binaryString(atoi(operand->value), COMMAND_VALUE_LENGTH);
        }
        printf("check here's the direct operand operandNode value: %s\n", operand->value);
        printf("check direct operand bmc value:%s\n", value);
    }
    else if(operand->type == REGISTER_OPERAND)
    { /** addressing method type 3*/
        encoding_type = ABSOLUTE;
        if(position == SRC_OPERAND){
            /** src register operands should encode the binary value of register number, and pad the value with 6 zeros */
            value = concat(decimal_to_binaryString(getRegisterNumberOfOperand(operand), COMMAND_REGISTER_LENGTH), decimal_to_binaryString(0, COMMAND_REGISTER_LENGTH));
            printf("check src register operand value:%s\n", value);
        } else {
            /** target register operands should start with 6 zeros, and then the binary value of the register value */
            value = concat(decimal_to_binaryString(0, COMMAND_REGISTER_LENGTH), decimal_to_binaryString(getRegisterNumberOfOperand(operand), COMMAND_REGISTER_LENGTH));
            printf("check dest register operand value:%s\n", value);
        }
    }
    else if(operand->type == INDEX_OPERAND)
    { /** addressing method type 2*/
        char* 			indexLabel			= "";
        int 			indexLabelAddress	= 0;
        OperandNode*	indexOperands		= NULL;
        indexOperands = getOperandListOfIndexOperand(operand->value);

        if(indexOperands != NULL)
        {
            printf("check not null \n");

            if(indexOperands -> next != NULL)
            {
                printf("check not null \n");
            }
        }

        /*printf("check here's the operand's list of index: %s\n",indexOperands->value);*/
        printf("check %s %d \n", indexOperands->value, indexOperands->type);

        indexLabel = extractIndexOperandLabel(operand->value);

        printf("check here's the indexLabel: %s\n", indexLabel);

        /** find the index label in the symbols table */
        if(!(isnumber(indexLabel)))
        {
            printf("check 1 \n");
            symbol = searchForSymbolByLabel(indexLabel);

            printf("check %d \n", symbol->address);
        }

        if(symbol == NULL){
            ERROR_PROGRAM(("Unknown symbol %s is a part of the index statement", indexLabel));
            return;
        }
        printf("check here's the label that was found: %s %d \n", symbol->label, symbol->feature);

        /** if it an external symbol, we encode a different ARE bits, as it  external not relocatable */
        if(symbol->feature == ext)
        {
			printf("check ext");
			
            encoding_type = EXTERNAL;
        
            /** add the external usage to the external symbols usage list*/
            addExternalStatementUsage(symbol->label, IC + MEMOERY_START_ADDRESS);
        }

        else
        {
            printf("check relocateable \n");

            encoding_type = RELOCATEABLE;
        }
        /***/
        indexLabelAddress = symbol->address;
        printf("check %d \n", indexLabelAddress);
        printf("check the label's address:%d\n", symbol->address);

        /** add the index label first */
        codeSection[IC] = concat(decimal_to_binaryString(indexLabelAddress, COMMAND_VALUE_LENGTH), decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));

        printf("check the label's codeSection[IC]:%s\n", codeSection[IC]);

        IC++;
   
		printf("check ic = %d \n", IC);
		
		printf("check index operands = %s \n", indexOperands->value);
		
        /** add the index operands */

        /*
        if (!(isnumber(indexOperands->value))) {*/
            /** in case that there's a macro inside the index parentheses  */
            /** macro, such as direct values, do not need to be reallocated they are absolute */
            /*encoding_type = ABSOLUTE;*/
            /** get the macro's number*/
            /*if (validateLabel(indexOperands->value) && searchForSymbolByLabel(indexOperands->value)->feature == macro)
            {
                value = decimal_to_binaryString(getSymbolAddress(indexOperands->value), COMMAND_VALUE_LENGTH);
            }
            printf("check here's the index operand operandNode value (should be macro): %s\n", indexOperands->value);
            printf("check direct operand bmc value:%s\n", value);
        }
        else
        {*/
            /** in case that there value inside the index parentheses is regular number */
            /*value = decimal_to_binaryString(atoi(operand->value), COMMAND_VALUE_LENGTH);
        }

        codeSection[IC] = concat(decimal_to_binaryString(indexLabelAddress, COMMAND_VALUE_LENGTH), decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));*/
        addOperandsValuesToCodeSection(indexOperands);
        return;
    }
    else
    {  /** then its a label operand */
        Symbol* 		symbol			= NULL;

        /** find the label in the symbols table */
        if(!(isnumber(operand->value)))
        {
            printf("check 2 %s \n", operand->value);
            symbol = searchForSymbolByLabel(operand->value);
            if(symbol == NULL)
            {
                ERROR_PROGRAM(("Unknown symbol %s", operand->value));
                return;
            }
            /** if it an external symbol, we encode a different ARE bits, as it  external not relocatable */
            if(symbol->feature == ext)
            {
                encoding_type = EXTERNAL;

                addExternalStatementUsage(symbol->label, IC + MEMOERY_START_ADDRESS);
            }
            else
            {
                encoding_type = RELOCATEABLE;
            }
        }
        value = decimal_to_binaryString(symbol->address, COMMAND_VALUE_LENGTH);

    }

    /** combine statement and the encoding type bits */
    codeSection[IC] = concat(value, decimal_to_binaryString(encoding_type, COMMAND_ARE_BITS_LENGTH));
    
    IC++;
}

void 		validateIfOperandsAreaAllowed	(OperandNode* operandsList, COMMANDS cmd)
{
    int 	operandsCount				 = 0;
    
    operandsCount = countNumberOfOpearnds(operandsList);
    
    switch (operandsCount)
    {
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

void 		validateOperandAllowedForCommand(OperandType operandType, COMMANDS cmd, OperandPosition operandPosition)
{
    CommandDescriptor* 		descriptor 		= NULL;
    boolean 				result 			= FALSE;
    
    descriptor = getCommandDescriptor(cmd);
    
    /** zero operands commands can't have any operand */
    if(descriptor->numberOfOperands == 0)
    {
		return;
	}
    
    /** single operand statements can only have Destination operands */
    if((descriptor->numberOfOperands == 1) && (operandPosition == TARGET_OPERAND))
    {
        return;
    }

    switch (operandPosition)
    {
        case SRC_OPERAND:
            if((descriptor->allowedSrcOperands[0] == operandType) || (descriptor->allowedSrcOperands[1] == operandType) || (descriptor->allowedSrcOperands[2] == operandType) || (descriptor->allowedSrcOperands[3] == operandType))
            {
                result = TRUE;
			}
            
            break;
        
        case TARGET_OPERAND:
            if((descriptor->allowedDestOperands[0] == operandType) || (descriptor->allowedDestOperands[1] == operandType) || (descriptor->allowedDestOperands[2] == operandType) || (descriptor->allowedDestOperands[3] == operandType))
            {
                result = TRUE;
			}
            
            break;
    }

    if(result == FALSE)
    {
        ERROR_PROGRAM(("invalid operator type for command"));
    }
}
