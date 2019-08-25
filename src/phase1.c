#include "phase1.h"
extern int currentLine;
void handleNextLIne(char* line);

void doPhase1(char* fileName){

    FILE *fileToAssemble = NULL;
    char* renamedInputFile = "";
    /** file names are given without the extension, we expect the file to end with the .as extension*/
    /*fileToAssemble = openReadFile(concat(fileName, ".as"));*/


    if (is_extention_exists (fileName, ".as"))
    {
		printf("check - the extention .as exists in %s\n", fileName);
        renamedInputFile = fileName;
        printf("check 2 the file name that we'll try to open %s\n", renamedInputFile);
    }
    else
    {
        printf("check - the extention .as does not exist in %s\n", fileName);
        renamedInputFile = rename_file(fileName, ".as");
        printf("check 8 \n");
    }
    if (open_or_create_file(&fileToAssemble,renamedInputFile) == 0)
    {

        printf("check 14 open or creation of %s was done successfully\n", renamedInputFile);
        /** keeps reading line by line and handle each line */
        doWhileFileHaveLines(fileToAssemble, handleNextLIne);
        /** after we handled all the lines, update the final addresses in the symbols table */
        updateSymbolTableAddresses();
        printSymbolTable();
    }
    else
    {
        fprintf(stderr,"ERROR: The file %s could not be renamed to %s%s",fileName,fileName,".as");
    }
    
    fclose(fileToAssemble);
}

void handleNextLIne(char* line)
{
    STATEMENT_TYPE type = getStatementTypeOfSentence(line);

    printf("check %d!!!!!!!!!!!!!!!!!!!!!!!! \n", type);

    /** skip empty lines or comment lines */
    if(isCommentStatementOrEmptyLine(line) == TRUE){
        currentLine++;
        return;
    }

    /** check if it data statment line, or command instruction line, and handle it as needed */
    if(type == COMMAND_STATEMENT){
        printf("\n\n\n\n\n\n check comman statement \n\n\n\n\n\n\n\n\n");
        increaseCommandInstructionsCountByStatement(line);
    } else if(type != INVALID_STATEMENT){
        handleDataStatement(line);
    } else {
        printf("error invalid command at line");
    }
    currentLine++;
}

void updateSymbolTableAddresses(){
    /*TODO: this part is suspected as the mem problem since this is what between the
     * first and the second scan - and the file is being scanned.*/
    Symbol *walker;
    printf("check 18 lets update the symbol table addresses according to IC and DC \n");
    walker = getSymbolsTableHead();
    while (walker){
        printf("check 19 get the next node in Symbol is done successfully.\n");
        /** skip external or command labels, as we don't need to update their addresses */
        if(walker->feature == dat)
        {
            printf("check 20 is ext or dat\n");
			walker->address += getInstructionsCount() + MEMOERY_START_ADDRESS;
        }
        
        walker = walker->next;   
    }
}

void	printSymbolTable ()
{
    Symbol *walker;
    printf("check 22 attempt to print the Symbol table\n");
    walker = getSymbolsTableHead();
    printf("check 23 here's the label at the Symbol table's head %s\n", walker->label);
    while (walker)
    {
        printf("%s \t %d \t %d \n", walker->label, walker->feature, walker->address);
        walker = walker->next;
    }

}
