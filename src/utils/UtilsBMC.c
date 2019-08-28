#include	"UtilsBMC.h"

int			to_decimal					(int power)											/** Calculates from power to decimal */
{	
	int			i, j;	
	
	for ( j = 2, i = 1 ; i < power ; i++)	
	{	
		j*= 2;	
	}	
	
	return j;	
}	
	
int			from_command_to_binary	(char op[], COMMANDS ope)							    /** Calculates the command value to binary */
{	
	int			i				= OPCODE;	
	int 		j				= FOURTH_BIT_VALUE;	
	
	printf("check %d \n", ope);
	
	while ( i != 0)	
	{	
		if (ope >= j)	
		{	
			printf("check %d > %d \n", ope, j);
			
			op[OPCODE - i] = '1';	
	
			ope -= j;	
		}	
	
		else	
		{			
			op[OPCODE - i] = '0';	
		}	
	
		printf("%c", op[OPCODE-i]);
		
		i--;	
	
		j /= 2;	
	}	
	
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	
	return TRUE;	
}	
	
int			from_operand_to_binary		(char opr[], OperandType oprtype)					/** Calculates the operand value to binary */
{	
	int			i				= OPERAND;	
	int 		j				= OPERAND;	
	
	printf("check got to operand %d \n", oprtype); 
	
	while ( i != 0)	
	{	
		if (oprtype >= j)	
		{	
			opr[OPERAND - i] = '1';	
	
			oprtype -= j;	
		}	
	
		else	
		{	
			opr[OPERAND - i] = '0';	
		}	
	
		printf("%c",opr[OPERAND - i]); 
	
		i--;	
	
		j /= 2;	
	}	
	
	printf("\n");
	
	return TRUE;	
}	
	
int			from_storage_to_binary		(char storage[], int stoperand)						/** Calculates the storage operand value to binary */
{	
	int			i				= STORAGE_OPERAND;	
	int			j				= THIRD_BIT_VALUE;	
	
	while ( i != 0)	
	{	
		if (stoperand >= j)	
		{	
			storage[STORAGE_OPERAND - i] = '1';	
	
			stoperand -= j;	
		}	
	
		else	
		{	
			storage[STORAGE_OPERAND - i] = '0';	
		}	
	
		i--;	
	
		j /= 2;	
	}	
	
	return TRUE;	
}	
	
short int 	from_string_to_int			(char* str)											/** Casting from string to integer */
{	
	short int 		num			= 0;	
	int 			counter, i	= 0;	
	int				j			= 1;	
		
	printf("check got to from string to int \n");	
	
	if (str[i] == '#')	
	{	
		i++;	
	}	
	
	printf("check string to int i = %d \n", i);	
	
	while(str[i] != '\0')	
	{	
		printf("check %c \n", str[i]);	
	
		i++;	
	}	
	
	i--;	
	
	printf("check i = %d \n", i);	
	
	printf("check num = %d, j = %d \n", num, j);	
	
	for (counter = 0 ; i >= counter ; counter++)											/** Calculate the value from string */
	{	
		printf("check str[%d] = %d \n",counter, str[i]);	
		num += (str[counter] - char_to_ascii) * j;	
	
		j *= 10;	
	
		printf("check num = %d, j = %d \n", num, j);	
	}	
	
	printf("check final num = %d break \n", num);	
	
	return num;	
}	
	
short int	from_binary_to_decimal		(char arr[], int* bitCounter, int useBits)			/** Calculate the  binary value in to decimal value */
{	
	short int		j, counter				= 0;	
	
	for ( j = 0 ; j <= useBits ; j++)	
	{	
		counter += ((int)(arr[j] - char_to_ascii) * to_decimal(*bitCounter));	
	
		(*bitCounter)--;	
	}	
	
	return counter;	
}	
	
short int 	from_label_to_bmc			(int tblValue);

short int   from_label_to_bmc           (int tblValue)                                      /** Calculate the label value in binary machine code */
{
	tblValue <<= 2;

	return tblValue;
}

short int 	possitive_or_negative_num	(char* opr, boolean isIndex, boolean isNegative)    /** Calculate a index or number value */
{
	unsigned short int	num			= 0;

	num = from_string_to_int(opr);

	printf("check num = %d \n", num);

	if (isNegative)
	{
		num -= 1;

		num = ~num;

		printf("check negative number = %d \n", num);
	}

	if (isIndex)
	{
		printf("check index \n");

		num <<= 2;

		printf("check num = %d \n", num);

		if(isNegative)
		{
			num -= SHORT_TO_14_BITS;
		}
	}

	printf("check num = %d \n", num);

	return num;
}

int			print_extern				(char* label, int* decimalAddress, char* filename)	/** Print extern to file */
{
	FILE*	pf								= NULL;
	char*	fileNameWithExtention			= "";
	
	fileNameWithExtention = concat(filename, ".ext");
	
	if (open_or_create_file(&pf, fileNameWithExtention) == -1)
	{
		return -1;
	}
	
	printf("check \t\t\t\t\t\t\t\t %s %d\n", label, *decimalAddress);
	
	fputs(label, pf);
	
	fputc('\t', pf);
	
	if (*decimalAddress < maxNumDecimalAddress)
	{
		fputc('0', pf);									                                    /** puts 0 before the IC number if it is less then 1000*/
	}
	
	fprintf(pf, "%d\n", *decimalAddress);
	
	fclose(pf);
	
	free(fileNameWithExtention);
	
	return 1;
}
