/* Includes				*/

#include 	<stdlib.h>
#include 	<string.h>
#include 	<stdio.h>
#include 	"../constants.h"
#include	"Error.h"

/* Defines				*/

#ifndef        ASSEMBLER_LIST_H
#define        ASSEMBLER_LIST_H

/* Structures			*/

typedef struct _listNode
{
    char*				data;
    struct _listNode* 	next;
} listNode;

typedef struct 
{
    int 				logicalLength;
    int 				elementSize;
    listNode* 			head;
    listNode*			tail;
} list;

/** Function Declaration	*/

/**
 * Creates a  list
 * @param list pointer to hold the new list
 * @param elementSize the size of each element in the list
 */
void 		list_new		(list*, int);

/**
 * Destroys the given list, frees up all it allocated memory
 * @param list
 */
void 		list_destroy	(list*);

/**
 * Adds the given element to the end of the list
 * @param list
 * @param element
 */
void 		list_append		(list*, char*);

/**
 * Returns the number of nodes in the given list
 * @param list
 * @return
 */
int 		list_size		(list*);

#endif
