#include "phase1.h"

void			doPhase1					(char* fileName) {
    FILE *fileToAssemble = NULL;

    if (open_or_create_file(&fileToAssemble, fileName) == 0)
    {
        /** keeps reading line by line and handle each line */
        doWhileFileHaveLines(fileToAssemble, handleNextLinePhase1);
        printf("check doWhileFileHaveLines was done for line %d\n", currentLine);

        /** after we handled all the lines, update the final addresses in the symbols table */
        updateSymbolTableAddresses();
    }
    else
    {
        ERROR_PROGRAM(("The file %s could not be renamed to %s%s",fileName,fileName,".as"));
    }
    printf("check about to close fileName: %s with this pointer:%p\n", fileName, (void*)fileToAssemble);
    fclose(fileToAssemble);
    printf("check fileName: %s with this pointer:%p was closed successfully\n", fileName, (void*)fileToAssemble);
}

void			handleNextLinePhase1		(char* line)
{
    STATEMENT_TYPE type = getStatementTypeOfSentence(line);

    /** skip empty lines or comment lines */
    if(isCommentStatementOrEmptyLine(line))
    {
        currentLine++;
        printf("check currentLine after isCommentStatementOrEmptyLine: %d\n", currentLine);
        return;
    }

    /** check if it data statement line, or command instruction line, and handle it as needed */
    if(type == COMMAND_STATEMENT)
    {
        increaseCommandInstructionsCountByStatement(line);
        printf("check increaseCommandInstructionsCountByStatement is ended\n");
    }
    
    else if(type != INVALID_STATEMENT)
    {
        handleDataStatement(line);
    }
    
    else
    {
        printf("error invalid command at line\n");
    }
    
    currentLine++;
    
    printf("check currentline after data or macro sentence= %d \n", currentLine);
}

void			updateSymbolTableAddresses	()
{
    Symbol* 	walker				= NULL;
    
    walker = getSymbolsTableHead();
    
    while (walker){
        /** skip external or command labels, as we don't need to update their addresses */
        if(walker->feature == dat)
        {
			walker->address += getInstructionsCount() + MEMOERY_START_ADDRESS;
        }
        
        walker = walker->next;   
    }
    printf("check updateSymbolTableAddresses is done\n");
}
