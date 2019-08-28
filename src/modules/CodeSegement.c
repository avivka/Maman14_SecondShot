#include "CodeSegement.h"

/** Static Data Members	*/

/** Instruction counter */
static  int 		IC 				= 0;

int 		getInstructionsCount		()
{
    return  IC;
}

void 		initCodeSection				(char* fileName, int dataCounter)
{
	char*	newFileName		= "";
	FILE*	fileToAssembler	= NULL;
	
	newFileName = concat(fileName, ".ob");
	
	printf("check %s filename \n", newFileName);
	
	if (open_or_create_file(&fileToAssembler, newFileName) == 0) 
    {
		printf("check ic = %d DC= %d \n", IC, dataCounter);
		fprintf(fileToAssembler, "\t %d %d \n", IC, dataCounter);
		
		fclose(fileToAssembler);
	}
	
	else
	{
		ERROR_PROGRAM(("The file %s could not be opened",newFileName));
	}
	free(newFileName);
}

void 		increaseCommandInstructionsCountByStatement	(char* statement)
{
    char* 			label 			= extractLabel(statement);
    Symbol* 		newSymbol 		= NULL;
    OperandNode* 	operandsList	= NULL;
    OperandNode* 	indexSrcOperand = NULL;
    OperandNode* 	indexDesOperand = NULL;
    int 			operandsCount 	= 0;

    printf("check here we try to get the label in command statement: %s %p\n", label, (void*)label);

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
            printf("check here's the label before I let it go in increaseCommandInstructionsCountByStatement: %s\n", label);
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
            printf("check here's the label before I let it go in increaseCommandInstructionsCountByStatement 2: %s\n", label);
            break;
        
        case 0:
        
            /** nothing to do */
            printf("check here's the label before I let it go in increaseCommandInstructionsCountByStatement 3: %s\n", label);
            break;
            
        default:
            printf("check here's the label before I let it go in increaseCommandInstructionsCountByStatement 4: %s\n", label);
            ERROR_PROGRAM(("invalid number of operands for a command statement, got %d, expected to be between 0 to 2", operandsCount));
            break;
    }

    if(label == NULL)
    {
        free(label);
    }
}


commandLine addStatementToCodeSegment	(char* statement)
{
	char* 				label					= "";
    int 				operandsCount			= 0;
    OperandNode* 		operandsSrcList			= NULL;
    CommandDescriptor*	descriptor				= NULL;
    COMMANDS 			commandEnum;
    commandLine         newLine;

    /** get rid of unneeded white spaces */
    removeExtraSpaces(statement);
    
    trimwhitespace(statement);
    
    label = extractLabel(statement);
    
    printf("check called \n");

    operandsSrcList = getOperandsListOfStatement(statement, COMMAND_STATEMENT, label);
    
    printf("check ok \n");

    operandsCount = countNumberOfOpearnds(operandsSrcList);
    
    printf("check operand count = %d \n", operandsCount);
    
    commandEnum = getCommandOfStatement(statement);
    
    printf("check command enum = %d \n", commandEnum);
    
    descriptor = getCommandDescriptor(commandEnum);
    
    printf("check descriptor != null \n");
    
    if(descriptor == NULL)
    {
        ERROR_PROGRAM(("unknown command"));
        printf("check here's the label before I let it go in addStatementToCodeSegment 1: %s\n", label);
        free(label);
        return newLine;
    }

    /** initialaize line in order to handle command coding with CreateBMC functionalities*/

    newLine.command = commandEnum;

    if(operandsCount != descriptor->numberOfOperands)
    {
        ERROR_PROGRAM(("invalid number of operands got %d, expected %d", operandsCount, descriptor->numberOfOperands));
    }

    validateIfOperandsAreaAllowed(operandsSrcList, commandEnum);

    switch (operandsCount)
    {    
        case 0:
        
            newLine.desoperand.type 	= NO_OPERAND;
            newLine.desoperand.value 	= "";
                              
            newLine.srcoperand.type 	= NO_OPERAND;
            newLine.srcoperand.value 	= "";
            
            break;
     
        case 1:
            
            newLine.desoperand = *operandsSrcList;
            
            newLine.srcoperand.type 	= NO_OPERAND;
            newLine.srcoperand.value 	= "";

            break;
        
        case 2:
			
			newLine.desoperand = *operandsSrcList ->next;
			
			operandsSrcList->next = NULL;
			
            newLine.srcoperand = *operandsSrcList;
        
            break;
    }

    printf("check here's the label before I let it go in addStatementToCodeSegment 2: %s\n", label);
    free(label);
    return newLine;
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
