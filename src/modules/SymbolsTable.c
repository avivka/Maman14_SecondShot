#include "SymbolsTable.h"
 /** data instructions counter */
static int DC = 0;

static Symbol *tableHead;
static Symbol *tableTail;

int getDataInstructionsCount(){
    return  DC;
}

void increaseDataInstructionsCount(){
    DC++;
}

Symbol* getSymbolsTableHead(){
    return  tableHead;
}

Symbol* getSymbolsTableTail(){
    return  tableTail;
}

void resetSymbolsModulesModule(){
    Symbol *temp;
    DC = 0; /** resets the data instructions count */
    /** free up the whole list memory */
    while (tableHead){
        temp = tableHead;
        tableHead = tableHead->next;
        free(temp);
    }
    /** avoid dangling pointers, verify that after memory was freed tableTail will stay NULL, note tableHead is garunted to be NULL after the while, due to the fact that we enfoce tail->NEXT will be NULL */
    tableTail = NULL;
}

void addSymbolToTable(Symbol *newSymbol)
{
    /*char*       label = "";*/
	printf("check 3 \n");
    Symbol *isSymbolExists = searchForSymbolByLabel(newSymbol->label);

    /** label already exists */
    if(isSymbolExists != NULL){
        ERROR_PROGRAM(("Requested label %s, already exists, can't declare the same label twice.", newSymbol->label));
    }
    /*
    label = concat(newSymbol->label, '\0');
    free(newSymbol->label);
    newSymbol->label = label;
    */
	printf("check important %s %d \n", newSymbol-> label, newSymbol-> address);

    /** if no tail, it means we are setting the first item in the table */
    if(tableTail == NULL){
		printf("check tail null \n");
		
        tableHead = tableTail = newSymbol;
        tableHead->next = NULL;
        return;
    }

    /** appends the new item to the end of the table */
    tableTail->next = newSymbol;
    tableTail = newSymbol;
    tableTail->next = NULL;

    printf("check done function addSymbolToTable \n");
}

Symbol* buildSymbol(char* label, labelFeature feature, int address){
   Symbol* newSymbol = malloc(sizeof(Symbol));
   errorIfMallocFailed(newSymbol, "while trying to allocate memory to create a new Symbol");
   newSymbol->label = label;
   newSymbol->feature = feature;
   newSymbol->address = address;
   newSymbol->next = NULL; /** protect pointer dangling, initialize it as NULL */
   return  newSymbol;
}

Symbol* searchForSymbolByLabel(char* label){
    Symbol *currentSymbol;

    currentSymbol = tableHead;

    while (currentSymbol){
		printf("check symbol table head pointer: %p\n", (void *)currentSymbol->label);
		printf("check yyy %s %s \n", currentSymbol->label, label);
        /** if matches, meaning we found the requested label */
        if(strcmp(currentSymbol->label, label) == 0){
            printf("check true \n");
            return  currentSymbol; /** returns pointer to the symbol with the requested label */
        }
        /** advance to next symbol */
        currentSymbol = currentSymbol->next;
    }

    /** could'nt find a symbol with the request label, returns NULL **/
    printf("check false \n");
    return  NULL;
}

int getSymbolAddress(char *symbolLabel){
    Symbol *symbol;
    printf("check 4 \n");
    symbol = searchForSymbolByLabel(symbolLabel);

    if(symbol == NULL){

        ERROR_PROGRAM(("Unknown symbol %s", symbolLabel));
        return  0;
    }
    printf("check here's the symbol in getSymbolAddress:%s\n", symbol->label);

    return  symbol->address;
}

void printSymbolTable ()
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