#include "Analyzer.h"


STATEMENT_TYPE getStatementTypeOfSentence(char* sentence){

    printf("check that we're in getStatementTypeOfSentence");
 if(isStatementTypeDataStatement(sentence))
     return DATA_STATEMENT_TYPE_DATA;

 if(isStatementTypeDataStatementEntry(sentence))
     return  DATA_STATEMENT_TYPE_ENTRY;

 if(isStatementTypeDataStatementExtern(sentence))
     return  DATA_STATEMENT_TYPE_EXTERN;

 if(isStatementTypeDataStatementString(sentence))
     return  DATA_STATEMENT_TYPE_STRING;

 if(isStatementTypeDataStatementDefine(sentence))
     return  DATA_STATEMENT_TYPE_DEFINE;

 if(isCommandStatement(sentence)) {
     return COMMAND_STATEMENT;
 }
 return  INVALID_STATEMENT;
}

int isDataStatement(char *sentence){
    STATEMENT_TYPE type = getStatementTypeOfSentence(sentence);

    printf("check isDataStatement %d", type);

    if(type == DATA_STATEMENT_TYPE_DATA || type == DATA_STATEMENT_TYPE_ENTRY || type == DATA_STATEMENT_TYPE_EXTERN || type == DATA_STATEMENT_TYPE_DEFINE || type == DATA_STATEMENT_TYPE_STRING)
        return  1;

    return 0;
}

int validateLabel(char* label){
    int i;
    if(strlen(label) <= 30 ){
        if((strlen(label) == 2 && label[0] == 'r')){
            if((label[1] >= 1 && label[1] <= '7')){
                ERROR_PROGRAM(("Label cant be named as register"));

                return 0;
            }
            else if (isalpha(label[1]) || isdigit(label[1]))
                return 1;
            else
              ERROR_PROGRAM(("Label Cannot contain signs"));

            return 0;
        }
        else if (!((strcmp(label, "mov") == 0) || (strcmp(label, "cmp") == 0) || (strcmp(label, "add") == 0) || (strcmp(label, "sub") == 0) ||
                   (strcmp(label, "lea") == 0) || (strcmp(label, "not") == 0) || (strcmp(label, "clr") == 0) || (strcmp(label, "inc") == 0) ||
                   (strcmp(label, "dec") == 0) || (strcmp(label, "jmp") == 0) || (strcmp(label, "bne") == 0) || (strcmp(label, "red") == 0) ||
                   (strcmp(label, "prn") == 0) || (strcmp(label, "jsr") == 0) || (strcmp(label, "rts") == 0) || (strcmp(label, "stop") == 0 )))
        {
            if (!isalpha(label[0])){
                ERROR_PROGRAM(("Label Cannot start with digits"));
                return 0;
            }
            for (i = 1; i < (strlen(label)); i++){
                if (!(isalpha(label[i]) || isdigit(label[i]))){
                    printf("This is the label: %s",label);
                    ERROR_PROGRAM(("Label contains signs"));
                    return 0;
                }
            }
            return 1;
        } else {
            ERROR_PROGRAM(("Label cannot be named as an instruction"));
            return 0;
        }
    } else{
        ERROR_PROGRAM(("Label is too long (more than 30 chars)"));
        return 0;
    }
}

char * extractLabel(char* sentence){
    const char ch = ':';
    char *buff;
    int i;
    buff = (char*)malloc(sizeof(char) * MAX_SIZE_OF_LABEL);
    i = 0;
    if(strchr(sentence, ch))
    {
        if((sentence[0] != ' ') && (sentence[0] != '\t'))
        {
            while(sentence[i] && sentence[i] != ':')
            {
                buff[i] = sentence[i];
                i++;
            }
        } else{
            ERROR_PROGRAM(("the label is contain spaces or tabs"));
            return NULL;
        }
        buff[i]='\0';
        validateLabel(buff);
        return buff;
    }
    else
        return  NULL;
}

char * extractIndexOperandLabel(char* indexOperandValue){
   char *buff;
    int i;
    i = 0;
    buff = (char*)malloc(sizeof(char) * MAX_SIZE_OF_LABEL);
   while (i < strlen(indexOperandValue) && indexOperandValue[i] != '['){
        buff[i] = indexOperandValue[i];
        i++;
    }

    if(strlen(buff) == 0){
        return  NULL;
   }

    return  buff;
} /*TODO: edit according to operand number 2*/

int isStatementTypeDataStatement(char* sentence) {
    char *result;
    char* string = ".data";
    int i;
    i = 1;
    result = strchr(sentence, '.');
    if(strlen(sentence) == 0)
        return 0;

    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t')){
            if(result[i] != string[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }
    else
        return 0;
}

int isStatementTypeDataStatementString(char* sentence){
    char *result;
    char* string = ".string";
    int i;
    i = 1;
    result = strchr(sentence, '.');
    if(strlen(sentence) == 0)
        return 0;

    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t')){
            if(result[i] != string[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }
    else
        return 0;
}

int isStatementTypeDataStatementEntry(char* sentence){
    char *result;
    char* string = ".entry";
    int i;
    i = 1;
    result = strchr(sentence, '.');
    if(strlen(sentence) == 0)
        return 0;
    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t')){
            if(result[i] != string[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }
    else
        return 0;
}

int isStatementTypeDataStatementExtern(char* sentence){
    char *result;
    char* string = ".extern";
    int i;
    i = 1;
    result = strchr(sentence, '.');
    if(strlen(sentence) == 0)
        return 0;
    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t')){
            if(result[i] != string[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }
    else
        return 0;
}


int isStatementTypeDataStatementDefine(char* sentence){
    char *result;
    char* string = ".define";
    int i;
    i = 1;
    result = strchr(sentence, '.');
    if(strlen(sentence) == 0)
        return 0;

    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t')){
            if(result[i] != string[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }
    else
        return 0;
}

boolean isCommentStatementOrEmptyLine(char *sentence){
    if(sentence[0] == ';' || sentence[0] == '\n') {
        return TRUE;
    }
    else {
        while(sentence && isspace(sentence[0])){
            sentence++;
        }
        if(sentence[0] == ';' || sentence[0] == '\0'){
            return TRUE;
        }
        else
            return FALSE;
    }
}

int isCommandStatement(char *sentence){
    COMMANDS command;

    command = getCommandOfStatement(sentence);

    printf("check command #2 %d \n", command);

    if(command != UNKNOWN_COMMAND)
    {
        printf("check good command \n");
        return 1;
    }

    return 0;

}

COMMANDS getCommandOfStatement(char *sentence){
    int labelLength = 0;
    int iterationIndex = 0;
    char* poteinailCommandString = "";
    char* commandString = "";
    char* label = "";
    COMMANDS command;
    commandString = malloc(sizeof(char) * 4);
    errorIfMallocFailed(commandString, "for a new string");
    removeExtraSpaces(sentence);
    sentence =  trimwhitespace(sentence);
    label = extractLabel(sentence);
    /** figure label offset */
    if(label == NULL)
        labelLength = 0;
    else
        labelLength = strlen(label) + 2; /** length of the label, + 1 for the :, + for the space after the label, guaranteed to be single space due to removeExtraSpaces*/
    iterationIndex = 0;
    poteinailCommandString = sentence + labelLength;
    printf("check 21 %s\n", poteinailCommandString);
    /*while(iterationIndex < (strlen(sentence) - labelLength) && iterationIndex <= MAX_COMMAND_LENGTH)*/
    while(iterationIndex < (strlen(poteinailCommandString)) && iterationIndex <= MAX_COMMAND_LENGTH)
    {
        commandString[iterationIndex] = poteinailCommandString[iterationIndex];
        printf("check 23: this should be the command: %s %d \n",commandString, iterationIndex);
        command = commandStringToEnum(commandString);

        /** if we already found the command return it */
        if(command != UNKNOWN_COMMAND)
        {
            printf("check 22 %d\n", command);
            return  command;
        }


        iterationIndex++;
    }
    printf("check 22 %d\n", command);

    return  UNKNOWN_COMMAND;


}
