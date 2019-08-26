#include 	"CreateBMC.h"

int			from_line_to_bmc	(commandLine* nextLine, int decimalAddress, list* symbolList, char* filename) 		/** The main function of creation binary machine code */
{												
	create_basic_bmc (nextLine, &decimalAddress, filename);				 											/** Creates the first binary machine code from the line (COMMANDS based) */
														
	if (nextLine->srcoperand != NULL)													
	{													
		from_src_des_opr (nextLine, symbolList, TRUE, &decimalAddress, filename);									/** Checks what kind of operand is it and transfers if to fourth base */
	}					
						
	if (nextLine->srctype == REGISTER_OPERAND && nextLine->destype == REGISTER_OPERAND)								/** Checks if the source and destination operands are storage type */
	{
		return decimalAddress;
	}
	
	if (nextLine->desoperand != NULL)
	{
		from_src_des_opr (nextLine, symbolList, FALSE, &decimalAddress, filename);									/* Checks what kind of operand is it and transfers if to fourth base */
	}	
	
	return decimalAddress;
}

short int	create_basic_bmc	(line* nextLine, int* decimalAddress, char* filename)										/* Creates the first binary machine code from COMMANDS */
{
	int 		bitCounter		= NUM_OF_ACTIVE_BITS - 5; 													/* Unused bits */
	short int	counter			= 0;
	char		op[OPCODE]		= "";
	char		opr[OPERAND]	= "";

	from_command_to_binary (op, nextLine->command);															/* Transfer command to binary */

	counter += from_binary_to_decimal(op, &bitCounter, OPCODE - 1);										/* Transfer from binary to decimal */
						
	from_operand_to_binary (opr, nextLine->srctype);														/* Transfer operand to binary */
						
	counter += from_binary_to_decimal(opr, &bitCounter, OPERAND - 1);										/* Transfer from binary to decimal */
						
	from_operand_to_binary (opr, nextLine->destype);														/* Transfer operand to binary */

	counter += from_binary_to_decimal(opr, &bitCounter, OPERAND - 1);										/* Transfer from binary to decimal */
	
	from_binary_machine_code_to_fourth_base(counter, decimalAddress, filename);

	return 0;
}

short int 	from_src_des_opr	(line* nextLine, list* symbolList, boolean isSrc, int* decimalAddress, char* filename)		/* Use to check if the operand is SRC to DES and by the case call the right function */
{
	if (isSrc)
	{
		printf("check src %d \n", nextLine->srctype);

		switch (nextLine->srctype)
		{
			case DIRECT_VALUE_OPERAND:																			/* Immediate address */
					return opr_immediate(symbolList, nextLine->srcoperand, decimalAddress, filename);
											
			case LABEL_OPERAND:																				/* Direct address */
					return opr_direct(nextLine->srcoperand, symbolList, FALSE, decimalAddress, filename);
											
			case INDEX_OPERAND:																				/* Index address */
				return opr_index(nextLine->srcoperand, symbolList, decimalAddress, filename);
						
			case REGISTER_OPERAND:																			/* Storage address */
				return src_des_storage(nextLine, decimalAddress, filename);

			default:
				ERROR_PROGRAM(("There is a problem with the source operand of the line"));
		}
	}

	else 																																			/* In case that the operand type's is destination */
	{
		printf("check des %d \n", nextLine->destype);

		switch (nextLine->destype)
		{
			case DIRECT_VALUE_OPERAND:																													/* Immediate address */
					return opr_immediate(symbolList, nextLine->desoperand, decimalAddress, filename);
											
			case LABEL_OPERAND:																														/* Direct address */
					return opr_direct(nextLine->desoperand, symbolList, false, decimalAddress, filename);
											
			case INDEX_OPERAND:																														/* Index address */
				return opr_index(nextLine->desoperand, symbolList, decimalAddress, filename);
						
			case REGISTER_OPERAND:																													/* Storage address */
				return src_des_storage(nextLine, decimalAddress, filename);

			default:
				ERROR_PROGRAM(("There is a problem with the destination operand of the line"));
		}
	}

	return -1;
}

short int 	opr_immediate		(list* symbolList, char* opr, int* decimalAddress, char* filename)							/* In case of Immediate operand create the binary machine code for it */
{	
	Symbol* 	currentSymbol	= NULL;
	
	if (*opr == '#')
	{
		opr = &opr[1];
	}
		
	if ((opr[0] >= FIRST_SMALL_LETTER_ASCII && opr[0] <= LAST_SMALL_LETTER_ASCII) || (opr[0] >= FIRST_CAPITAL_LETTER_ASCII && opr[0] <= LAST_CAPITAL_LETTER_ASCII)) 	/* Checks if the character is a letter */
	{
		printf("check got here \n");
		
		currentSymbol = searchForSymbolByLabel(opr);																	/* Checks if the label is in the table */
		
		return from_binary_machine_code_to_fourth_base (from_label_to_bmc(currentSymbol->address), decimalAddress, filename);		/* Adds the ARE section and returns it */
	}
	
	if (opr[0] == '-')																										/* Checks if the number is negative */
	{
		printf("check got to negative \n");
		
		return from_binary_machine_code_to_fourth_base (possitive_or_negative_num(&opr[1], TRUE, FALSE), decimalAddress, filename);	/* Calculates the negative number */
	}
	
	return from_binary_machine_code_to_fourth_base (possitive_or_negative_num(&opr[0], TRUE, FALSE), decimalAddress, filename);	/* Calculates the positive number */
}

short int 	opr_direct			(char* label, list* symbolList, boolean isIndex, int* decimalAddress, char* filename)		/* Creates binary machine code by label, internal or external */
{
	short int 	bmc						= 0;
	Symbol* 	currentSymbol			= NULL;
		
	currentSymbol = searchForSymbolByLabel(label);														/* Search the label in the table and return pointer to it */
																							
	if (currentSymbol == NULL)																						
	{																						
		return -1;																						
	}																						
																							
	if (isIndex && currentSymbol->feature != dat)
	{																						
		return -1;
	}
																							
	bmc = from_label_to_bmc(currentSymbol->address);														/* Move the bits to make place for ARE */
																							
	if (currentSymbol->feature == ext)																		/* Adds the correct value of the ARE in case of external label */
	{	
		print_extern(label, decimalAddress, filename);
																							
		bmc += 1;																						
	}																						

	else																									/* Adds the correct value of the ARE in unexternal cases */
	{
		bmc += 2;
	}
	
	return from_binary_machine_code_to_fourth_base (bmc, decimalAddress, filename);
}

short int 	opr_index			(char* ope, list* symbolList, int* decimalAddress, char* filename)							/* In case of index operand create the binary machine code for it and for the label */
{ /*TODO: needs to be in enum? why is it passed as char*?*/
	char		label[MAX_SIZE_OF_LABEL]		= "";
	int 		i						= 0;
	int			j						= 0;
	
	for ( ; ope[i] != '\0' ; i++)																			/* Separate the label from the rest*/
	{
		if (ope[i] != '[')
		{
			label[i] = ope[i];
		}
		
		else
		{			
			break;
		}
	}
	
	if (ope[i] == '\0')
	{
		ERROR_PROGRAM(("There is a problem with the operand of the line"));
		
		return -1;
	}
	
	opr_direct(label, symbolList, TRUE, decimalAddress, filename);													/* Creates binary machine code from the label */
	
	for ( i++ ; ope[i] != '\0' ; i++, j++)																	/* Separates the index from the rest of the operand */
	{
		if (ope[i] != ']')
		{
			label[j] = ope[i];
		}
		
		else
		{
			break;
		}
	}
	
	if (ope[i] == '\0')
	{
		ERROR_PROGRAM(("There is a problem with the operand of the line"));
		
		return -1;
	}
	
	label[j] = '\0';
	
	return opr_immediate (symbolList, label, decimalAddress, filename);													/* creates binary machine code from the index */
	
}

short int	src_des_storage		(line* nextLine, int* decimalAddress, char* filename)										/* In case the operand is storage type */
{
	int 		bitCounter				= NUM_OF_ACTIVE_BITS - 7; 		/* Unused bits */
	short int	counter					= 0;
	char		sto[STORAGE_OPERAND]	= "";

	if (nextLine->srctype == REGISTER_OPERAND)
	{
		from_storage_to_binary(sto, (nextLine->srcoperand[1] - char_to_ascii));

		counter += from_binary_to_decimal(sto, &bitCounter, STORAGE_OPERAND - 1);
	}

	else
	{
		bitCounter -= STORAGE_OPERAND;																												/* Unused bits */
	}

	if (nextLine->destype == REGISTER_OPERAND)
	{
		from_storage_to_binary(sto, (nextLine->desoperand[1] - char_to_ascii));

		counter += from_binary_to_decimal(sto, &bitCounter, STORAGE_OPERAND - 1);
	}

	return from_binary_machine_code_to_fourth_base (counter, decimalAddress, filename);
}

