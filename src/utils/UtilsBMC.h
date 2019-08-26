/* Includes 	*/

#include 	<stdio.h>
#include    "../phase1.h"
#include    "../modules/CommandsIndex.h"

/*  Definitions	*/

#define		SHORT_TO_14_BITS			49152							/* The value of the last two bits */
#define		LAST_CAPITAL_LETTER_ASCII	122
#define		FIRST_CAPITAL_LETTER_ASCII	97			
#define		LAST_SMALL_LETTER_ASCII		90
#define		FIRST_SMALL_LETTER_ASCII	65
#define		FOURTH_BIT_VALUE			8
#define		THIRD_BIT_VALUE				4
#define		OPCODE						4
#define		STORAGE_OPERAND				3
#define		OPERAND						2

/*	Prototypes	*/

int			to_decimal					(int);							/* Calculates from power to decimal */
int			from_operation_to_binary	(char [], command);			/* Calculates the operation value to binary */
int			from_operand_to_binary		(char [], OperandType);			/* Calculates the operand value to binary */
int			from_storage_to_binary		(char [], int);					/* Calculates the storage operand value to binary */
int			print_extern				(char*, int*, char*);					/* Print extern to file */
short int 	from_string_to_int			(char*);						/* Casting from string to integer */
short int	from_binary_to_decimal		(char [], int*, int);			/* Calculate the  binary value in to decimal value */
short int 	from_label_to_bmc			(int);							/* Calcules the label value in binary machine code */
short int 	possitive_or_negative_num	(char*, boolean, boolean);		/* Calculate a index or number value */
/*Symbol*		test_label					(char*, Symbol*); TODO: need to be changed to symbolList
void		printArray					(char []);
void		printDecimal				(short int num);*/





