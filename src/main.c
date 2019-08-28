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

		printf("check the filename is - %s \n", fileName);

		rename(*argv, fileName);
		
		/** checks if the file exists and delete them if so*/

		deleteFile(fileName, ".ob");
				
		deleteFile(fileName, ".ext");
		
		deleteFile(fileName, ".ent");

        printf("\n Begin processing the following file: %s\n", *argv);

        currentLine = 0;
        printf("check currentLine before scan 1: %d\n", currentLine);

        errorFlag = 0;

        /** execute phase 1 of the assembler */
        doPhase1(fileName);
        
        printf("check done phase 1 \n");
        /** resets line read, because reading the file from the start */
        currentLine = 0;
        printf("check currentLine after scan 1: %d\n", currentLine);

        /*TODO: Add if statement that checks if the scan failed and FREE the symbol table and the data segment if it happens*/

		if(errorFlag == 0)
		{
			/** execute phase 2 of the assembler */        
			doPhase2(fileName);
			
			printf("check phase2 done \n");
			
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

        printf("\n Assembler completed processing file: %s", *argv);

		extendedFileName = concat(fileName, ".as");

        rename(fileName, extendedFileName);

        printf("check filename:%s\n", extendedFileName);

        free(extendedFileName);
    }

    return  0;
}
