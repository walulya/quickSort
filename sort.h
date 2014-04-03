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
#ifndef _SORT_H
#define _SORT_H

const int INPUT_SIZE = 10000;
#define STACKSIZE  INPUT_SIZE/2
//typedef enum { false, true } bool;

void init_threads(pthread_t* threads, int size, void *(*func)(void *));

 void wait_for_threads(pthread_t* threads, int size);

void* work_thread(void *);




#endif
