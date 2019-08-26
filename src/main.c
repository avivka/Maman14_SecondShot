#include "main.h"

<<<<<<< HEAD
    if(argc < 2) {
        ERROR_PROGRAM(("Arguments weren't supplied, exiting code \n"));
=======
int			main			(int argc, char *argv[]) {
	
	char* 	fileName 		= "";

    if(argc < 2) 
    {
        fprintf(stderr, "Error: Arguments weren't supplied, exiting code \n");
    
>>>>>>> 03a17e9235e68b601c2bfb97f1422bca28d229fc
        exit (0);
    }

    /** init the map that defines all the commands rules */
    initCommandsDescriptors();

    for(argc--, argv++; argc; argv++, argc--) {
<<<<<<< HEAD
        printf("\n Begin processing the following file: %s\n", *argv);
=======
		
		if(check_if_file_exists(*argv) != 0)
		{
			ERROR_PROGRAM(("There is no file name %s \n", *argv));
			
			break;
		}
		
		fileName 	= is_extention_exists(*argv, ".as");
		
		printf("check the filename is - %s \n", fileName);
		
		rename(*argv, fileName);
		
        printf("\n Begin processing the following file: %s", *argv);
        
>>>>>>> 03a17e9235e68b601c2bfb97f1422bca28d229fc
        currentLine = 1;
        
        errorFlag = 0;
        
        /** execute phase 1 of the assembler */
        doPhase1(fileName);

        /** rests line read, because reading the file from the start */
        currentLine = 1;
        
        /** execute phase 2 of the assembler */
        doPhase2(fileName);
        
        printf("check phase2 done \n");

        /** clear up so we can process properly the next file*/
        resetDataSegmentModule();
        resetSymbolsModulesModule();
        resetCodeSegmentModule();

        printf("\n Assembler completed processing file: %s", *argv);
        
        rename(fileName, concat(fileName, ".as"));
    }
        return  0;
}
