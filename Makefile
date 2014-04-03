# Makefile for executable stacktest

# *****************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS = -pedantic -Wall -g

# ****************************************************
# Entries to bring the executable up to date

sort: sort.o stack.o partition.o
	$(CC) $(CFLAGS) -o sort sort.o stack.o partition.o

sort.o: sort.c stack.h
	$(CC) $(CFLAGS) -c sort.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

partition.o: partition.c partition.h
	$(CC) $(CFLAGS) -c partition.c

clean:
	rm -f *.o sort
