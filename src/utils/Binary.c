#include "Binary.h"


unsigned int* 	int_to_bin_digit			(unsigned int in, int count)
{						
    int 			i							= 0;
    unsigned int* 	out							= 0;
    unsigned int 	mask						= 0;
			
    out = (unsigned int*) malloc(sizeof(int) * count);
    errorIfMallocFailed(out, "couldn't allocate memory for a new binary number");
		
    mask = 1U << (count-1);		
			
    for (i = 0; i < count; i++)		
    {		
        out[i] = (in & mask) ? 1 : 0;		
        in <<= 1;		
    }		
			
    return  out;		
}		
		
char* 			decimal_to_binaryString		(int n, int numOfDigits)
{
    int 		c						= 0;
    int 		d						= 0;
    int 		count					= 0;
    char* 		pointer					= NULL;

    pointer = (char*) malloc (numOfDigits + 1);
    errorIfMallocFailed(pointer, "couldn't allocate memory for a new binary string");

    for (c = numOfDigits - 1 ; c >= 0 ; c--)
    {
        d = n >> c;

        if (d & 1)
        {
            *(pointer + count) = 1 + '0';
		}
        
        else
        {
            *(pointer + count) = 0 + '0';
		}

        count++;
    }
    
    *(pointer + count) = '\0';

    return  pointer;
}

int 			data_from_binary_machine_code_to_fourth_base (char* binaryCode, int* decimalAddressCounter, FILE* fp)
{
    int 		evenCounter						= 0;
    int			oddCounter						= evenCounter++;
    char		sign							= '0';

    if (*decimalAddressCounter < maxNumDecimalAddress)
    {

        fputc('0', fp); 							/**puts 0 before the IC number if it is less then 1000*/
    }

    fprintf(fp, "%d", *decimalAddressCounter);

    (*decimalAddressCounter)++;

    fputc('\t', fp);

    while (evenCounter < NUM_OF_ACTIVE_BITS)
    {
		sign = to_4_base_data(binaryCode[evenCounter], binaryCode[(oddCounter)]);
		
		if (sign == '0')
		{
			return -1;
		}
		
		fputc(sign, fp);
		
		evenCounter 	+= 2;
		oddCounter 		+= 2;
    }

    fputc('\n', fp);

    return TRUE;
}

/*Returns * or # or % or ! to the array. Reutrns 0 if all good.*/

char			to_4_base_data				(char firstBit, char secondBit)
{
    secondBit 	= (secondBit - char_to_ascii) * 2;
    firstBit	= (firstBit - char_to_ascii);

    switch(secondBit + firstBit)
    {
        case 0:
            /* return * to the array*/
            return '*';

            break;

        case 1:
            /* return # to the array*/
            return '#';

            break;

        case 2:
            /* return % to the array*/
            return '%';

            break;

        case 3:
            /* return ! to the array*/
            return '!';

            break;

        default:
            /* write error*/
        ERROR_PROGRAM(("There is a problem with the translation to 4 base \n"));
            return '0';

            break;
    }

    return '0';
}
