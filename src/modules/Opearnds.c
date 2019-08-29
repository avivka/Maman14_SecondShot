/* Includes		*/

#include "Opearnds.h"
#include "../utils/TextUtils.h"
#include "../utils/List.h"

int 			instructionLengthByStatmentType	(STATEMENT_TYPE statementType, char *statement);
OperandNode* 	createOperandNode				(char *operandValue, STATEMENT_TYPE statementType);
boolean 		isRegisterValue					(char* value);

OperandNode* 	getOperandsListOfStatement		(char* statement, STATEMENT_TYPE statementType, char* label)
{
	int 			labelLength 			= 0;
	int 			instructionLength		= 0;
	int 			stringIterationIndex 	= 0;
	int 			operandStartIndex		= 0;
	char* 			Operandvalue 			= "";
	OperandNode* 	headOfList 				= NULL;
	OperandNode* 	tail 					= NULL;
	OperandNode* 	temp 					= NULL;
	
	/** first get rid o any extra spaces */
	removeExtraSpaces(statement);
    
    /** figure label offset */
    if(label == NULL)
    {
        if(statementType == DATA_STATEMENT_TYPE_DATA || statementType == DATA_STATEMENT_TYPE_STRING)
        {
            ERROR_PROGRAM((".data or .string instructions must start with label"));
        }
        labelLength = 0;
	}
    
    else
    {
        labelLength = strlen(label) + 2;	 /** length of the label, + 1 for the :, + for the space after the label, guaranteed to be single space due to removeExtraSpaces*/
	}

    instructionLength = instructionLengthByStatmentType(statementType, statement);

    
    stringIterationIndex = labelLength + instructionLength +1; /** the label length + the instruction length + one for the space before the operand  e.g: MAIN: sub */
    
    /** iterate over each char in the statement, starting from the first char that should be included in the operand's section.*/
    operandStartIndex = stringIterationIndex;


    while (stringIterationIndex <= strlen(statement)) {
        /** if we hit parentheses it a suspected index addressing method, Keep collecting the whole expression as a whole */
        if (isCharsEqual(statement[stringIterationIndex], '[')) {
            /** continue until either we reached the end of the string, or we found our closing pair of parentheses*/
            while (!isCharsEqual(statement[stringIterationIndex], ']') && stringIterationIndex < strlen(statement) &&
                   (!isCharsEqual(statement[stringIterationIndex], '\n'))) {/**changed back from '[' to ']'*/
                stringIterationIndex++;
            }


            /** if we hit the end without the last char to be the closing parentheses, error */
            if (!isCharsEqual(statement[stringIterationIndex], ']')) {
                ERROR_PROGRAM(("no matching closing ], each [ must have a closing ]"));
            }

            /** continue one more to get after parentheses to \0 or other illegal char */
            stringIterationIndex++;
        }

        /** if it the end of current operand, we */
        if (isspace(statement[stringIterationIndex]) || isCharsEqual(statement[stringIterationIndex], ',') == TRUE ||
            isCharsEqual(statement[stringIterationIndex], '\0') == TRUE) {
            /** zero length operand value, means we actually have no operand */
            if (operandStartIndex == stringIterationIndex) {
                break;
            }


            /** add the operand to the list */
            Operandvalue = substringFromTo(statement, operandStartIndex, stringIterationIndex);

            temp = createOperandNode(Operandvalue, statementType);

            if (headOfList == NULL) {


                headOfList = tail = temp;
            } else {


                tail->next = temp;

                tail = temp;
            }



            if (statementType == DATA_STATEMENT_TYPE_DEFINE) {
                if (headOfList == NULL) {

                    ERROR_PROGRAM(("something went wrong with the macro's label"));
                }



                validateLabel(headOfList->value);

                Operandvalue = getOperandFromDefine(statement, stringIterationIndex);



                if ((strcmp(Operandvalue, ""))) {
                    tail->next = createOperandNode(Operandvalue, DATA_STATEMENT_TYPE_DEFINE);

                    if (tail->next == NULL) {
                        ERROR_PROGRAM(("something went wrong with the macro's value"));

                        return NULL;
                    }
                } else {
                    ERROR_PROGRAM(("there is no second operand in the macro definition"));

                    return NULL;
                }

                return headOfList;
            }

            /** if are at the end of the string, then we collected the last operand and its time to stop */
            if (isCharsEqual(statement[stringIterationIndex], '\0') == TRUE) {
                break;
            }

            /** keep iterating until we reach the start of next operand */
            while (isspace(statement[stringIterationIndex]) ||
                   isCharsEqual(statement[stringIterationIndex], ',') == TRUE) {
                stringIterationIndex++;
            }

            operandStartIndex = stringIterationIndex;


        } else {
            stringIterationIndex++;
        }
    }

    return  headOfList;
}

char* 			getOperandFromDefine 			(char* operand, int index)
{
	int				endOperand 		= 0; 
	char*			operandValue	= "";
	
	while(isspace(operand[index]) || isCharsEqual(operand[index], '\0') == TRUE)
	{
		if(operand[index] == '\0')
		{
			ERROR_PROGRAM(("Define statemant must include second operand"));
			break;
		}
                
		index++;

	}
	
	if(operand[index] != '=')
	{
		ERROR_PROGRAM(("Define statemant must include '=' sign"));
	}
	
	index++;
	
	while(isspace(operand[index]) || isCharsEqual(operand[index], '\0') == TRUE)
	{
		if(operand[index] == '\0')
		{
			ERROR_PROGRAM(("Define statemant must include second operand"));
			break;
		}
                
		index++;

	}

	
	endOperand = index;
	
	while(check_if_number(operand[endOperand]))
	{
		endOperand++;
	}

	
	operandValue = substringFromTo(operand, index, endOperand);

	
	while(isspace(operand[endOperand]) || operand[endOperand] == '\0')
	{
		if (operand[endOperand] == '\0')
		{
			break;
		}
		
		endOperand++;
	}

	
	if(operand[endOperand] != '\0')
	{
		ERROR_PROGRAM(("Define statemant must include not more than two operands"));
	}
	
	return operandValue;
}

OperandNode* 	createOperandNode				(char *operandValue, STATEMENT_TYPE statementType)
{
    char 			expected		= '\0';
    OperandNode* 	newNode			= (OperandNode *) malloc(sizeof(OperandNode));
    errorIfMallocFailed(newNode, "When trying to allocate memory for a new operand node.");
    
    newNode->next =NULL;	 /** dangling pointers protection */

	
    switch (statementType)
    {
        case DATA_STATEMENT_TYPE_DATA:
        
            /**check if the operand is a number*/
            if (!(isnumber(operandValue)))
            {
                if ((searchForSymbolByLabel(operandValue)) == NULL)
                {
                    ERROR_PROGRAM(("invalid operand %s, should be macro or a number", operandValue));
                }
            }
            
            /** inserts the value of newNode->value with the '#' */
            newNode->value = operandValue;
            newNode->type = DIRECT_VALUE_OPERAND;
            
            break;
        
        case DATA_STATEMENT_TYPE_STRING:

            if(!isWordStartsWithChar(operandValue, '"'))
            {
                ERROR_PROGRAM(("unexpected token in .string operand, expected %s, got %c at value %s", &expected, operandValue[0], operandValue));
            }
            
            if(!isWordEndsWithChar(operandValue, '"'))
            {
                ERROR_PROGRAM(("unexpected token in .string operand, expected %s, got %c at value %s", &expected, getLastChar(operandValue), operandValue));
            }
            
            newNode->value = substringFromTo(operandValue, 1, strlen(operandValue) - 1); /** extract the value from the quotes */
            newNode->type = DIRECT_VALUE_OPERAND;
            
            break;
        
        case DATA_STATEMENT_TYPE_EXTERN:
        
        case DATA_STATEMENT_TYPE_ENTRY:
        
            if(!validateLabel(operandValue))
            {
                ERROR_PROGRAM(("invalid label %s", operandValue));
            }
            
            /** set the value as is as its a label*/
            newNode->value = operandValue;
            newNode->type = LABEL_OPERAND;
            
            break;
        
        case DATA_STATEMENT_TYPE_DEFINE:
		
			if(!(isnumber(operandValue)))
			{
				newNode->value = operandValue;
				newNode->type = LABEL_OPERAND;
			}
		
			else
			{
				newNode->value = operandValue;
				newNode->type = DIRECT_VALUE_OPERAND;
			}
		
			break;
        
        case COMMAND_STATEMENT:

        
            if (isContainsChar(operandValue, '['))
            {
                newNode->type = INDEX_OPERAND;
                newNode->value = operandValue;
            }
        
            else if(isWordStartsWithChar(operandValue, '#') || isnumber(operandValue))
            {
               newNode->value = substringFromTo(operandValue, 1, strlen(operandValue));
               newNode->type = DIRECT_VALUE_OPERAND;
            }
            
            else if(isRegisterValue(operandValue))
            {
                newNode->type = REGISTER_OPERAND;
                newNode->value = operandValue;
            }
            
            else
            {
                if(!(isnumber(operandValue)))
                {
					if (!(validateLabel(operandValue)))
					{
						ERROR_PROGRAM(("invalid label %s", operandValue));
					}
                }
            
                /** set the value as is as its a label*/
                newNode->value = operandValue;
                newNode->type = LABEL_OPERAND;
            }
        
            break;
        
        default:
        
            break;
    }
    
    return newNode;
}

OperandNode* 	getOperandListOfIndexOperand	(char* indexOperandString)
{
        char* 			indexOperandValue 	= "";
        char* 			walker 				= "";
        OperandNode* 	list 				= NULL;
        int 			labelLength 		= 0;
        int 			operandEndIndex 	= 0;
        int 			operandStartIndex 	= 0;
        char* 			label 				= extractIndexOperandLabel(indexOperandString);

        if(label == NULL)
        {
            ERROR_PROGRAM(("index operand must have a label that defines where to index to"));
            free(label);
            return NULL;
        }

        
        labelLength = strlen(label);

        
         /** label length + open [ brace */
        operandStartIndex = operandEndIndex = labelLength + 1;

        
        walker = indexOperandString + labelLength + 1;
        
        while (walker && *walker != ']')
        {
            operandStartIndex++;
            walker++;
        }


        indexOperandValue = substringFromTo(indexOperandString, operandEndIndex, operandStartIndex);

        list = createOperandNode(indexOperandValue, COMMAND_STATEMENT);

        list->next = NULL;


        free(label);
        return list;
}

boolean 		isRegisterValue					(char* value)
{
    /** register must be two chars long, first charmust be lowercase r, second char must be between 0 to 7 */
    if(strlen(value) == 2 && value[0] == 'r' && (int) value[1] >= NUMBER_ZERO_ASCII_CODE &&  (int) value[1] <= NUMBER_SEVEN_ASCII_CODE)
    {
        return  TRUE;
	}

    return  FALSE;
}

int 			getRegisterNumberOfOperand		(OperandNode *operand)
{
    if(operand->type != REGISTER_OPERAND)
    {
        ERROR_PROGRAM(("called getRegisterNumberOfOperand with non register operand"));
    
        return 0;
    }
    
    return atoi(&operand->value[1]);
}

int 			instructionLengthByStatmentType(STATEMENT_TYPE statementType, char *statement)
{
    COMMANDS cmdType;


    switch(statementType)
    {
        case DATA_STATEMENT_TYPE_DATA:
    
            return  5; /** instruction of .data is 5 chars long */
    
        case DATA_STATEMENT_TYPE_STRING:
    
            return  7;  /** instruction of .string is 7 chars long */
    
        case DATA_STATEMENT_TYPE_ENTRY:
    
            return  6; /** instruction of .entry is 6 chars long */
    
        case DATA_STATEMENT_TYPE_EXTERN:
    
            return  7; /** instruction of .extern is 7 chars long */
    
        case DATA_STATEMENT_TYPE_DEFINE:
    
            return  7; /** instruction of .define is 7 chars long */
    
        case COMMAND_STATEMENT:
    
            /** only command statement is with 4 chars all other are 3 */
            cmdType = getCommandOfStatement(statement);
    
             if(cmdType == stop)
             {
                 return  4;
			 }
            
            return  3; /** all other command statements are 3 letters */
        
        default:
        
            return  0;
    }
}

int 			countNumberOfOpearnds			(OperandNode* operandsList)
{
    int 			count 			= 0;
    OperandNode* 	walker			= operandsList;
    
    while (walker)
    {
        count++;
    
        walker = walker->next;
    }
    
    return count;
}