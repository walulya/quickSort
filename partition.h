/*
 *         File: partition.h
 *         Author: Ivan <ivanw@chalmers.se>
 *         Last Modified: April 1, 2014
 *         Project: Quicksort - Work-stealing Implementation
 * ----------------------------------------------------------------
 *
 * OVERVIEW:
 * =========
 */
#include <stdio.h>
#ifndef _PARTITION_H
#define _PARTITION_H

int partition(sortElementT* input, int p, int r);

stackElementT* do_sort(stackElementT *);

void try_sort();

void print(int *input, int size);
void printChunck(int *input,stackElementT* chunk);

#endif
