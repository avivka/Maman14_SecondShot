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

	
	while ( i != 0)	
	{	
		if (ope >= j)	
		{
			
			op[OPCODE - i] = '1';	
	
			ope -= j;	
		}	
	
		else	
		{			
			op[OPCODE - i] = '0';	
		}	

		
		i--;	
	
		j /= 2;	
	}	

	
	return 0;	
}	
	
int			from_operand_to_binary		(char opr[], OperandType oprtype)					/** Calculates the operand value to binary */
{	
	int			i				= OPERAND;	
	int 		j				= OPERAND;	

	
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

	
		i--;	
	
		j /= 2;	
	}	

	
	return 0;	
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
	
	return 0;	
}	
	
short int 	from_string_to_int			(char* str)											/** Casting from string to integer */
{	
	short int 		num			= 0;	
	int 			counter, i	= 0;	
	int				j			= 1;	

	
	if (str[i] == '#')	
	{	
		i++;	
	}	

	
	while(str[i] != '\0')	
	{
	
		i++;	
	}	
	
	i--;	


	
	for (counter = 0 ; i >= counter ; counter++)											/** Calculate the value from string */
	{
		num += (str[counter] - char_to_ascii) * j;	
	
		j *= 10;	

	}	
	

	
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




	if (isNegative)
	{
		num -= 1;

		num = ~num;

	}

	if (isIndex)
	{

		num <<= 2;


		if(isNegative)
		{
			num -= SHORT_TO_14_BITS;
		}
	}


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
