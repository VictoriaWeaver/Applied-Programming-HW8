# -------------------------------------------------------------------------
# Sample makefile for GNU/Linux system
# To compile and test interp module
# -------------------------------------------------------------------------
## Flags for GCC
CC = gcc
CFLAGS = -Wall -ansi -pedantic 
DFLAGS = -g

## WARNING, for indentation use one TAB, not spaces
## Main "body" of makefile.
hw8:
	$(CC) $(CFLAGS) $(DFLAGS)

interp.o: interp.c interp.h
	$(CC) $(CFLAGS) $(DFLAGS)

valgrind: hw8
	valgrind --tool=memcheck --leak-check=yes ./hw8 -cl data.txt

construct: hw8


evaluate: hw8


plots:


## Cleaning up auxiliary files 31 
clean:
    rm -f *.o
