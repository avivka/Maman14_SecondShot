/* Includes				*/

#include "SymbolsTable.h"
#include "Opearnds.h"
#include "../utils/Error.h"
#include "../utils/List.h"

/* Defines				*/

#ifndef ASSEMBLER_DATASEGMENT_H
#define ASSEMBLER_DATASEGMENT_H

/* Structures			*/

typedef struct data_segment_node {
    int value;
    struct data_segment_node *next;
} DataSegmentNode;

/* Prototypes	*/

/**
 * resets the Data Segment module, re-init it,
 *  frees up all the memory
 */
void 				resetDataSegmentModule		();

/**
 * @return the head of the data segment.
 */
DataSegmentNode* 	getDataSegmentHead			();

/**
 * @return reference to the entryStatements list
 */
list* 				getEntryStatementsList		();

void 				addExternalStatementUsage	(char*, int);

/**
 * This functions handles any type of dataStatments, and add it properly acoording to the statement type
 * Data statements are of the types .data, .string, .entry, .extern, and or declartions of labels e.g MAIN: mov r3,LENGTH
 * the function adds as needed new labels to the symbols table, adds the data segments as needed, and increases the data statements counter as needed.
 * @param dataStatement a string of any data statement.
 */
void 				handleDataStatement			(char*);
#endif
