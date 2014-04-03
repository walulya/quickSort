#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "stack.h"
#include "partition.h"
#include "sort.h"
#include <sys/time.h>

#include <unistd.h>

bool end_of_data = false;

//const int INPUT_SIZE = 10;

int id = 1;

stackT stack;

int input[INPUT_SIZE];

int main(int argc, char *argv[])
{

    unsigned char workers = 5;
    // If we've got a parameter, assume it's the number of workers to be used
    if (argc > 1)
    {  
        // Values less than 1, or parameters that aren't numbers aren't allowed
        if (atoi(argv[1]) < 1)
        {
            printf("Usage: %s [workers]\n", argv[0]);
            return 1;
        }

        // Set the number of workers to be used
        workers =  atoi(argv[1]);
    }

	srand(time(NULL));
    	for(size_t i = 0; i < INPUT_SIZE; ++i)
		input[i] = rand() % INPUT_SIZE; 

    printf("Num workers: %d, input: %d\n", workers, INPUT_SIZE); 

    
    StackInit(&stack, STACKSIZE);

    //print(input, INPUT_SIZE);
    pthread_t thread_id[workers];

    init_threads(thread_id, workers, work_thread);
    usleep(20);

    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    
    stackElementT chunk = (stackElementT){0, INPUT_SIZE-1,id++, false};
	
    do_sort(&chunk);

    end_of_data = true;
    wait_for_threads(thread_id, workers);

   gettimeofday(&tv2, NULL);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));


    //print(input, INPUT_SIZE);
    StackDestroy(&stack);
    return 0;
}


stackElementT* do_sort(stackElementT *chunk)
{
	if(chunk->begin >= chunk->end ){
		chunk->promise = true;
		//printf("Finished %d\n", chunk->id);
		return chunk;
	}

	 int j = partition(input,chunk->begin, chunk->end);

	stackElementT lower_chunk = (stackElementT){chunk->begin, j-1,id++, false};
	stackElementT upper_chunk = (stackElementT){j+1, chunk->end,id++, false};
	
	StackPush(&stack, &lower_chunk);
		usleep(30);

	/*printf("***********************\n");
	printf("lower %d id: %d\n", lower_chunk.begin, lower_chunk.id);	
	printChunck(input,&lower_chunk);
	printf("upper %d id: %d\n", upper_chunk.begin, upper_chunk.id);	
	printChunck(input,&upper_chunk);
	printf("***********************\n");
       */
	 
	do_sort(&upper_chunk);

	while(lower_chunk.promise == false)
	{
		//printf(" while lower %d %d id: %d\n", lower_chunk.begin, lower_chunk.end, lower_chunk.id);	
		//printf("while upper %d %d id: %d\n", upper_chunk.begin, upper_chunk.end, upper_chunk.id);	
		try_sort();
		usleep(2);
	}

	chunk->promise = true;
		
	return chunk;	
}

void init_threads(pthread_t* threads, int size, void *(*func)(void *))
{
	int i;
	for(i=0; i < size; i++)
	{
		pthread_create( &threads[i], NULL, func, NULL );
	}
}



void wait_for_threads(pthread_t* threads, int size)
{
	int i;
	for(i=0; i < size; i++)
	{
		pthread_join( threads[i], NULL);
	}
}

void try_sort()
{
	if(!StackIsEmpty(&stack)) {	
		stackElementT* chunk =  StackPop(&stack);
		//printf("chuck %d %d\n", chunk->begin, stack.top);	
		if(chunk != NULL){
		    do_sort(chunk);
		    //printf("chuck %d %d\n", chunk->id, (int)pthread_self());	
		}
	}
}

void* work_thread(void *det)
{
	while(end_of_data == false)
	{
		try_sort();
	}
	return NULL;
}
