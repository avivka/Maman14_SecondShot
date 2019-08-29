#include "main.h"

int			main			(int argc, char *argv[])
{
	char* 	fileName 			= "";
	char*	extendedFileName	= "";

    if(argc < 2)
    {
        ERROR_PROGRAM(("Arguments weren't supplied, exiting code \n"));

        exit (0);
    }

    /** init the map that defines all the commands rules */
    initCommandsDescriptors();

    for(argc--, argv++; argc; argv++, argc--)
    {

		if(check_if_file_exists(*argv) != 0)
		{
			ERROR_PROGRAM(("There is no file name %s \n", *argv));

			break;
		}

		fileName = is_extention_exists(*argv, ".as");


		rename(*argv, fileName);
		
		/** checks if the file exists and delete them if so*/

		deleteFile(fileName, ".ob");
				
		deleteFile(fileName, ".ext");
		
		deleteFile(fileName, ".ent");

        printf("\nBegin processing the following file: %s\n", *argv);

        currentLine = 1;

        errorFlag = 0;

        /** execute phase 1 of the assembler */
        doPhase1(fileName);

        /** resets line read, because reading the file from the start */
        currentLine = 1;

		if(errorFlag == 0)
		{
			/** execute phase 2 of the assembler */
			doPhase2(fileName);

			
			if(errorFlag == 1)
			{
				deleteFile(fileName, ".ob");
				
				deleteFile(fileName, ".ext");
				
				deleteFile(fileName, ".ent");	
			}
		}

        /** clear up so we can process properly the next file*/
        resetDataSegmentModule();
        resetSymbolsModulesModule();
		resetICAndCounter();
		
        printf("\nAssembler completed processing file: %s\n", *argv);

		extendedFileName = concat(fileName, ".as");

        rename(fileName, extendedFileName);

        free(extendedFileName);
    }

    return  0;
}
