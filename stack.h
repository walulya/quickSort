/*  
 *        File: stack.h
 *        Author: Ivan <ivanw@chalmers.se>
 * 	  Last Modified: Array 1, 2014
 *        Project: Stack - Array Implementation
 * ----------------------------------------------------------------
 *
 * This is the interface for a stack of characters.
 */
#include <pthread.h>
#ifndef _STACK_H
#define _STACK_H

typedef int sortElementT;
typedef enum { false, true } bool;

typedef struct stackElementT
{
	//stackElementT* begin;
	//stackElementT* end;
	int begin;
	int end;
	int id;
        bool promise;
} stackElementT;


typedef struct {
    stackElementT **contents;
    int maxSize;
    int top;
    pthread_mutex_t mutex; 
} stackT;

void StackInit(stackT *stackP, int maxSize);

void StackDestroy(stackT *stackP);

void StackPush(stackT *stackP, stackElementT* element);
stackElementT* StackPop(stackT *stackP);

int StackIsEmpty(stackT *stackP);
int StackIsFull(stackT *stackP);


#endif  /* not defined _STACK_H */
