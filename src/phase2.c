#include "phase2.h"
#include "utils/List.h"

void handleNextLine(char* line);
void createEnteriesFile(char *fileName);
void createExternalsFile(char *fileName);
void createObjectFile(char *fileName, int codeSegmentSize, int dataSegmentSize);

extern int currentLine;

void doPhase2(char* fileName)
{
	int 	codeSegmentSize		= 0;
    int 	dataSegmentSize		= 0;
    FILE* 	fileToAssembler		= NULL;
    /*char*   renamedInputFile 	= "";*/
    
    if(fileToAssembler == NULL)
    {
		printf("check is null 1!\n");
	}

    printf("check 24 got to doPhase2\n");

    codeSegmentSize = getInstructionsCount();
    printf("check 24 here's the IC %d\n", codeSegmentSize);
    dataSegmentSize = getDataInstructionsCount();
    printf("check 24 here's the DC %d\n", dataSegmentSize);

    /** file names are given without the extension, we expect the file to end with the .as extension*/

    /*if (is_extention_exists (fileName, ".as"))
    {
        printf("check 1 again - the extention .as exists in %s\n", fileName);
        renamedInputFile = fileName;
        printf("check 2 again the file name that we'll try to open %s\n", renamedInputFile);
    }
    else
    {
        printf("check again - the extention .as does not exist in %s\n", fileName);
        renamedInputFile = rename_file(fileName, ".as");
        printf("check 8 again\n");
    }*/
    
    if (open_or_create_file(&fileToAssembler,fileName) == 0) 
    {
        printf("check 14 again open or creation of %s was done successfully\n", fileName);
        
        /*fclose(fileToAssembler);*/
		
        /** creates the proper size for the codeSegment as we now know it, and resets the IC count to 0, so we can build the code segement statement after statement */
        initCodeSection();
        /** keeps reading line by line and handle each line */
        doWhileFileHaveLines(fileToAssembler, handleNextLine);
        /*DoWhileFileHaveLines(renamedInputFile, handleNextLine);*/
        /*fclose(fileToAssembler);*/
        if (errorFlag == 1) {
            printf("didn't output files for file %s, because errors were found. see the errors output for more information.", fileName);
            return;
        }
        
        createEnteriesFile(fileName);
        createExternalsFile(fileName);
        createObjectFile(fileName, codeSegmentSize, dataSegmentSize);
        
        printf("check WTF \n");
        
        /*if (fileToAssembler != NULL)
		{
			printf("check closed corectly \n");
			
			if(fclose(fileToAssembler) == 0)
			{
				printf("check went good \n");
			}
		}*/
		        
        printf("check close phase2 \n");
    }

    else
    {
        fprintf(stderr,"ERROR: The file %s could not be renamed to %s%s",fileName,fileName,".as");
    }
}

void handleNextLine(char* line){
    /** skip empty lines or comment lines */
    if(isCommentStatementOrEmptyLine(line) == TRUE){
        currentLine++;
        return;
    }

    /** skip data statements lines we already handled them in phase 1 */
    if(isDataStatement(line)){
        currentLine++;
        return;
    } else if(isCommandStatement(line)){
        addStatementToCodeSegment(line);
    } else { /*TODO: add macro case and not call addStatementToCodeSegment(line) */
        ERROR_PROGRAM(("error invalid command"));
    }
    currentLine++;
}

void createEnteriesFile(char *fileName){

	printf("check got here \n");
    listNode *walker = NULL;
    list *entryList = NULL;
    int address = 0;
    int count = 0;
    char** buffer = NULL;
    entryList = getEntryStatementsList();
    walker = entryList->head;
    /** if not entry statements nothing to do */
    if(walker == NULL){
        return;
    }
    buffer = (char * *) malloc(sizeof(char *) * list_size(entryList));
    errorIfMallocFailed(buffer, "new array of strings");
    count = 0;
    while (walker)
    {
        address = getSymbolAddress((char *)walker->data);
        buffer[count] = (char *) malloc(sizeof(char *));
        errorIfMallocFailed(buffer[count], "while tring to allocate memory to buffer[count]");
        sprintf(buffer[count], "%s    %d", walker->data, address);
        walker = walker->next;
        count++;
    }

    writeToFile(concat(fileName, ".ent"), buffer, count);
}

void createExternalsFile(char *fileName)
{
    listNode *walker;
    list *externalsList;
    char * * buffer;
    int count;
    externalsList = getExternalStatementsList();
    walker = externalsList->head;
    /** if not entry statements nothing to do */
    if(walker == NULL){
       return;
    }
    buffer = (char**) malloc(sizeof(char *) * list_size(externalsList));
    errorIfMallocFailed(buffer, "new array of strings");
    count = 0;
    while (walker){
        buffer[count] = (char *) malloc(sizeof(char *));
        errorIfMallocFailed(buffer[count], "while tring to allocate memory to buffer[count]");
        sprintf(buffer[count], "%s", walker->data);
        walker = walker->next;
        count++;
    }

    writeToFile(concat(fileName, ".ext"), buffer, count);
    
    printf("check done external \n");
}

void createObjectFile(char *fileName, int codeSegmentSize, int dataSegmentSize)
{
    FILE* 				file 				= NULL;
    int 				itteratorIndex		= 0;
    int 				decimalAddress		= MEMOERY_START_ADDRESS;
    char** 				codeSegment			= getCodeSection();
    char* 				firstLine			= NULL;
    char* 				lineValue			= NULL;
    DataSegmentNode* 	dataSegmentWalker 	= NULL;

    fileName = concat(fileName, ".ob");
    
    if (open_or_create_file(&file,fileName) != 0)
	{
        fprintf(stderr, "error could not create file: %s \n", fileName);
        exit(1);
    }
    firstLine = (char *)malloc(sizeof(char*));
    errorIfMallocFailed(firstLine, "while tring to allocate memory to the first line");
    /** first put the total code instructions and total data instructions */
    sprintf(firstLine, "%d %d \n", codeSegmentSize, dataSegmentSize);
    fputs(firstLine, file);
    
    /** write all the code section to the file line by line */
    printf("check code segment = %d \n", codeSegmentSize);
    
    while (itteratorIndex < codeSegmentSize)
    {
		printf("\n check itterator = %d \n", itteratorIndex);
       /** prints each line to the weird binary value */
        from_binary_machine_code_to_fourth_base(codeSegment[itteratorIndex], &decimalAddress, file);
        
        itteratorIndex++;
    }

    dataSegmentWalker = getDataSegmentHead();
    
    if(dataSegmentWalker == NULL)
    {
		printf("check walker is null \n");
	}
	
	else
	{
		printf("check walker is not null \n");
	}
	
    /** write all the data section to the file line by line */
    while (dataSegmentWalker != NULL)
    {
        /** turn each value in data segment to it binary value in MACHINE_CODE_LINE_LENGTH bits */
        lineValue = decimal_to_binaryString(dataSegmentWalker->value, MACHINE_CODE_LINE_LENGTH);
        /** replace each line to it weird binary value */
        from_binary_machine_code_to_fourth_base(lineValue, &decimalAddress, file);
        /*** put the correct address for each line, which is the memory start + where the code section ended + the current place in data section */
        dataSegmentWalker = dataSegmentWalker->next;
    }
    
    free(firstLine);
    
    fclose(file);
    
    printf("check good file close! \n");
}
