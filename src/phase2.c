#include "phase2.h"
#include "utils/List.h"

void handleNextLine(char* line);

extern int currentLine;


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
    } else {
        ERROR_PROGRAM(("error invalid command"));
    }
    currentLine++;
}


