#include "phase1.h"

void			doPhase1					(char* fileName) {
    FILE *fileToAssemble = NULL;

    if (open_or_create_file(&fileToAssemble, fileName) == 0)
    {
        /** keeps reading line by line and handle each line */
        doWhileFileHaveLines(fileToAssemble, handleNextLinePhase1);

        /** after we handled all the lines, update the final addresses in the symbols table */
        updateSymbolTableAddresses();
    }
    else
    {
        ERROR_PROGRAM(("The file %s could not be renamed to %s%s",fileName,fileName,".as"));
    }

    fclose(fileToAssemble);
}

void			handleNextLinePhase1		(char* line)
{
    STATEMENT_TYPE type = getStatementTypeOfSentence(line);

    /** skip empty lines or comment lines */
    if(isCommentStatementOrEmptyLine(line))
    {
        currentLine++;
        return;
    }

    /** check if it data statement line, or command instruction line, and handle it as needed */
    if(type == COMMAND_STATEMENT)
    {
        increaseCommandInstructionsCountByStatement(line);
    }
    
    else if(type != INVALID_STATEMENT)
    {
        handleDataStatement(line);
    }
    
    else
    {
        printf("error invalid command at line");
    }
    
    currentLine++;
    
    printf("check currentline = %d \n", currentLine);
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
}
