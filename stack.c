/*
 *        File: stack.c
 *        Author: Ivan Walulya <ivanw@chalmers.se>
 *        Last Modified: Array 1, 2014
 *        Topic: Stack - Array Implementation
 * ----------------------------------------------------------------
 *
 * This is an array implementation of a character stack.
 */

#include <stdio.h>
#include <stdlib.h>  /* for dynamic allocation */
#include "stack.h"

/************************ Function Definitions **********************/

void StackInit(stackT *stackP, int maxSize)
{
    stackElementT **newContents;
    
    /* Allocate a new array to hold the contents. */
    
    newContents = (stackElementT **)malloc(sizeof(stackElementT *) * maxSize);
    
    if (newContents == NULL) {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    stackP->contents = newContents;
    stackP->maxSize = maxSize;
    stackP->top = -1;  /* I.e., empty */
    pthread_mutex_init(&stackP->mutex, NULL);
}

void StackDestroy(stackT *stackP)
{
    /* Get rid of array. */
    free(stackP->contents);
    
    stackP->contents = NULL;
    stackP->maxSize = 0;
    stackP->top = -1;  /* I.e., empty */
    pthread_mutex_destroy(&stackP->mutex);
}

void StackPush(stackT *stackP, stackElementT* element)
{
    if (StackIsFull(stackP)) {
        fprintf(stderr, "Can't push element on stack: stack is full.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    /* Put information in array; update top. */
   
   pthread_mutex_lock (&stackP->mutex);
    stackP->contents[++stackP->top] = element;
   pthread_mutex_unlock (&stackP->mutex);
}

stackElementT* StackPop(stackT *stackP)
{
    pthread_mutex_lock (&stackP->mutex);
    if (StackIsEmpty(stackP)) {
        //fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
        //exit(1);  /* Exit, returning error code. */
	pthread_mutex_unlock (&stackP->mutex);
	return NULL;
    }
    
    stackElementT* temp = stackP->contents[stackP->top--];
    pthread_mutex_unlock (&stackP->mutex);
    return temp;
}

int StackIsEmpty(stackT *stackP)
{
    return stackP->top < 0;
}

int StackIsFull(stackT *stackP)
{
    return stackP->top >= stackP->maxSize - 1;
}
