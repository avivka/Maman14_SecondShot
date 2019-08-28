#include "phase2.h"

char* 	exFileName		= "";
int		decimalAddress	= 100;

void			doPhase2			(char* fileName)
{
    int 	dataSegmentSize		= 0;
    FILE* 	fileToAssembler		= NULL;
   
    printf("check got to phase2 %s \n", fileName);    
    
    exFileName = fileName;
    
    printf("check ok \n");
    
    printf("check %s \n", exFileName);
    
    if(fileToAssembler == NULL)
    {
		printf("check is null 1!\n");
	}

    printf("check 24 got to doPhase2\n");

    dataSegmentSize = getDataInstructionsCount();


    /** file names are given without the extension, we expect the file to end with the .as extension*/
    
    if (open_or_create_file(&fileToAssembler,fileName) == 0) 
    {
        printf("check 14 again open or creation of %s was done successfully\n", fileName);
		
        /** creates the proper size for the codeSegment as we now know it, and resets the IC count to 0, so we can build the code segement statement after statement */
        initCodeSection(exFileName, dataSegmentSize);
       
        /** keeps reading line by line and handle each line */
        doWhileFileHaveLines(fileToAssembler, handleNextLine);
     
        if (errorFlag == 1)
        {
            printf("didn't output files for file %s, because errors were found. see the errors output for more information.", fileName);
        
            return;
        }
        createEnteriesFile(fileName);
        printDataSegmentToObjectFile(exFileName,dataSegmentSize, decimalAddress);
        
        printf("check WTF \n");
        
        if (fileToAssembler != NULL)
		{
			printf("check closed correctly \n");
			
			if(fclose(fileToAssembler) == 0)
			{
				printf("check went good \n");
			}
		}

        printf("check close phase2 \n");
    }

    else
    {
        ERROR_PROGRAM(("The file %s could not be opened",fileName));
    }
}

void 			handleNextLine		(char* line)
{
    commandLine     newLine;

    /** skip empty lines or comment lines */
    if (isCommentStatementOrEmptyLine(line))
    {
        currentLine++;
        
        return;
    }

    /** skip data statements lines we already handled them in phase 1 */
    if (isDataStatement(line))
    {
        currentLine++;
        printf("check currentLine after isDataStatement: %d\n", currentLine);
    
        return;
    }
    
    else if (isCommandStatement(line))
    {
		printf("check command statement \n");
		
        newLine = addStatementToCodeSegment(line);
        
        decimalAddress = from_line_to_bmc(&newLine, decimalAddress, exFileName);

        currentLine++;
        printf("check currentLine after isCommandStatement: %d\n", currentLine);

        return;
    }
    
    else
    {
        ERROR_PROGRAM(("error invalid command"));
    }
}

void 			createEnteriesFile	(char *fileName)
{
	int 		address 			= 0;
    int 		count 				= 0;
    char** 		buffer 				= NULL;
    list* 		entryList 			= getEntryStatementsList();
    listNode*	walker 				= entryList->head;
    char*		filename			= "";
    
    printf("check got to create \n");

    /** if not entry statements nothing to do */
    if (walker == NULL)
    {
        return;
    }
    
    buffer = (char**) malloc(sizeof(char) * MAX_SIZE_OF_LABEL * list_size(entryList));
    errorIfMallocFailed(buffer, "new array of strings");
    
    while (walker)
    {
        address = getSymbolAddress((char *)walker->data);
        
        buffer[count] = (char *) malloc(sizeof(char *));
        errorIfMallocFailed(buffer[count], "while tring to allocate memory to buffer[count]");
        
        if (address < maxNumDecimalAddress)
		{
			sprintf(buffer[count], "%s \t 0%d", walker->data, address);									/*puts 0 before the IC number if it is less then 1000*/							
		}
        
        else
        {
			sprintf(buffer[count], "%s \t %d", walker->data, address);
        }
        
        walker = walker->next;
        
        count++;
    }
    
    filename = concat(fileName, ".ent");

    writeToFile (filename, buffer, count);
    
    free(filename);
}

void 			printDataSegmentToObjectFile	(char *fileName, int dataSegmentSize, int decimalAddressCount)
{
    FILE* 				file 				= NULL;
    int 				decimalAddress		= decimalAddressCount;
    char* 				lineValue			= NULL;
    char*	            newFileName		    = "";
    DataSegmentNode* 	dataSegmentWalker 	= NULL;

    newFileName = concat(fileName, ".ob");

    printf("check the starting DecimalAddress: %d", decimalAddress);

	printf("check %s filename in printDataSegmentToObjectFile\n", newFileName);

    if (open_or_create_file(&file,newFileName) == 0)/*TODO: add error in case that the file cannot be opened because it shouldn't be there.*/
    {
        dataSegmentWalker = getDataSegmentHead();

        /** write all the data section to the file line by line */
        while (dataSegmentWalker != NULL)
        {
            /** turn each value in data segment to it binary value in MACHINE_CODE_LINE_LENGTH bits */
            lineValue = decimal_to_binaryString(dataSegmentWalker->value, MACHINE_CODE_LINE_LENGTH);
            printf("check line value: %s\n", lineValue);

            /** replace each line to it weird binary value */
            data_from_binary_machine_code_to_fourth_base(lineValue, &decimalAddress, file);

            /*** put the correct address for each line, which is the memory start + where the code section ended + the current place in data section */
            dataSegmentWalker = dataSegmentWalker->next;
        }
    }
	else
	{
		ERROR_PROGRAM(("The file %s could not be opened",newFileName));
	}
    
        fclose(file);
        
        free(newFileName);
}
