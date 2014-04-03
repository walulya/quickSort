/*
 *         File: partition.c
 *         Author: Ivan <ivanw@chalmers.se>
 *         Last Modified: April 1, 2014
 *         Project: Quicksort - Work-stealing Implementation
 * ----------------------------------------------------------------
 *
 * OVERVIEW:
 * =========
 */
#include "stack.h"
#include "partition.h"


int partition(sortElementT* input, int p, int r)
{
    int pivot = input[r];

    while ( p < r )
    {
        while ( input[p] < pivot )
            p++;

        while ( input[r] > pivot )
            r--;

        if ( input[p] == input[r] )
            p++;
        else if ( p < r )
        {
            int tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;
        }
    }

    return r;
}

void print(int *input, int size)
{
    for ( int i = 0; i < size; i++ )
       printf("%d ", input[i]);
    printf("\n");
}

void printChunck(int *input,stackElementT* chunk)
{
    for ( int i = chunk->begin; i <= chunk->end; i++ )
       printf("%d ", input[i]);
    printf("\n");
}


