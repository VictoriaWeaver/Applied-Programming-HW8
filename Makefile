# -------------------------------------------------------------------------
# Sample makefile for GNU/Linux system
# To compile and test interp module
# -------------------------------------------------------------------------
## Flags for GCC
CC = gcc
CFLAGS = -Wall -ansi -pedantic 
DFLAGS = -g
FILE = data.txt
EFILE = eval.txt

## WARNING, for indentation use one TAB, not spaces
## Main "body" of makefile.

hw8: Dynamic.o interp.o
	$(CC) $(CFLAGS) $(DFLAGS) hw8.c -o hw8 DynamicArrays.o interp.o

interp.o: interp.c interp.h
	$(CC) $(CFLAGS) $(DFLAGS) -c interp.c

Dynamic.o: DynamicArrays.c DynamicArrays.h
	$(CC) $(CFLAGS) $(DFLAGS) -c DynamicArrays.c

valgrind: hw8
	valgrind --tool=memcheck --leak-check=yes ./hw8 -nat $(FILE)
	valgrind --tool=memcheck --leak-check=yes ./hw8 -cl $(FILE)
	valgrind --tool=memcheck --leak-check=yes ./hw8 -nak $(FILE)

construct: hw8
	./hw8 -nat $(FILE) > sparameters1.txt
	./hw8 -cl $(FILE) > sparameters2.txt
	./hw8 -nak $(FILE) > sparameters3.txt

evaluate: hw8
	./hw8 -e sparameters1.txt $(EFILE) > eresults1.txt
	./hw8 -e sparameters2.txt $(EFILE) > eresults2.txt
	./hw8 -e sparameters3.txt $(EFILE) > eresults3.txt

plots:


## Cleaning up auxiliary files 31 
clean:
	rm -f *.o
