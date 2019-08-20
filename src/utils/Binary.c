#include "Binary.h"
#include "Error.h"
#include "FileReader.h"


unsigned int* int_to_bin_digit(unsigned int in, int count)
{
    int i;
    unsigned int* out;
    unsigned int mask;
    out = (unsigned int*) malloc(sizeof(int) * count);
    errorIfMallocFailed(out, "couldn't allocate memory for a new binary number");

    mask = 1U << (count-1);
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
    return  out;
}


char *decimal_to_binaryString(int n, int numOfDigits)
{
    int c, d, count;
    char *pointer;

    count = 0;
    pointer = (char*)malloc(numOfDigits+1);

   errorIfMallocFailed(pointer, "couldn't allocate memory for a new binary string");

    for (c = numOfDigits - 1 ; c >= 0 ; c--)
    {
        d = n >> c;

        if (d & 1)
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';

        count++;
    }
    *(pointer+count) = '\0';

    return  pointer;
}

int 	from_binary_machine_code_to_fourth_base 	(int short binaryCode, int* decimalAddressCounter, char* filename)
{
    int 	counter 						= 0;
    char 	number 							= '\0';
    char	bmcsign[NUM_OF_ACTIVE_BITS/2]	= "";
    char*	filenamewithextention			= "";
    FILE	*pf								= NULL;

    if (binaryCode == -1)
    {
        return -1;
    }

    filenamewithextention = rename_file(filename, ".ob");

    if (open_or_create_file(&pf, filenamewithextention) == -1)
    {
        free(filenamewithextention);
        return -1;
    }

    if (*decimalAddressCounter < maxNumDecimalAddress)
    {

        fputc('0', pf); 							/*puts 0 before the IC number if it is less then 1000*/
    }

    fprintf(pf, "%d", *decimalAddressCounter);

    (*decimalAddressCounter)++;

    fputc('\t', pf);

    while (counter < (NUM_OF_ACTIVE_BITS / 2))
    {
        if (binaryCode % 2 == 1)
        {

            if (number == '\0')
            {
                number = '1';
            }

            else
            {
                bmcsign[counter] = to_4_base(number, '1');

                if (bmcsign[counter] == '0')
                {
                    free(filenamewithextention);
                    return -1;
                }

                number = '\0';

                counter++;
            }
        }

        else
        {
            if (number == '\0')
            {
                number = '0';
            }

            else
            {
                bmcsign[counter] = to_4_base(number, '0');

                if (bmcsign[counter] == '0')
                {
                    free(filenamewithextention);
                    return -1;
                }

                number = '\0';

                counter++;
            }
        }

        binaryCode>>= 1;
    }

    printSignToFile(bmcsign, pf);

    fputc('\n', pf);

    free(filenamewithextention);

    fclose(pf); /*TODO: write functions that deal properly with files cleanup (such as clean_output_files)*/

    return 0;
}

/*Returns * or # or % or ! to the array. Reutrns 0 if all good.*/

char			to_4_base					(char firstBit, char secondBit)
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

int			printSignToFile					(char *bmcsign, FILE* fp)
{
    int i;

    for (i = (NUM_OF_ACTIVE_BITS/2 - 1) ; i >= 0 ; i--)
    {
        if(bmcsign[i] != '0')
        {
            fputc(bmcsign[i], fp);
        }

        else
        {
            return -1;
        }
    }

    return 0;
}

