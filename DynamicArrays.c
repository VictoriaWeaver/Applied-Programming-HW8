/************************************************************************
* Victoria Weaver
* vew4644@rit.edu
*
* Homework 1, Program to implement a dynamic array "abstract data type" 
*	as a C module.  Get familiar with the use of memory allocation and 
*	deallocation functions in the standard library, stdlib.
*
*************************************************************************/

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "DynamicArrays.h"


/**************************************************************************
* CreateDArray 
*   Allocates memory and initializes DArray with specified initial size.
**************************************************************************/
void CreateDArray( DArray *DArrayPtr, unsigned int InitialSize ){
	/* Initialize dynamic array as empty */
	DArrayPtr->EntriesUsed = 0;
	DArrayPtr->Capacity = InitialSize;

	/* Check the capacity of the array to allocate space (or not if 0)*/
	if(DArrayPtr->Capacity == 0){
		DArrayPtr->Payload = NULL;
	}
	else{
		DArrayPtr->Payload = (double*) malloc(DArrayPtr->Capacity * sizeof(double));

		/* Check if malloc was successful */
		if(DArrayPtr->Payload == NULL){
			fprintf(stderr, "CreateDArray(): malloc failed!\n");
			fflush(stderr);
		}
	}

}

/**************************************************************************
* PushToDArray
* Adds data to the end (push) of dynamic array and updates ElementsUsed 
*   If full, realocates memory space according to growth policy
* postcond: returns the index to the last element added 
**************************************************************************/
unsigned int PushToDArray( DArray *DArrayPtr, double *PayloadPtr ){
	/* If the array is full, increase the size */
	if(DArrayPtr->EntriesUsed == DArrayPtr->Capacity){
		DArrayPtr->Capacity += GROWTH_AMOUNT;

		/* Reallocate heap memory to reflect the new size of the dynamic array */
		DArrayPtr->Payload = realloc(DArrayPtr->Payload, DArrayPtr->Capacity * sizeof(double));
	
		/* Check if realloc was successful */
		if(DArrayPtr->Payload == NULL){
			fprintf(stderr, "PushToDArray(): realloc failed!\n");
			fflush(stderr);
		}
	}

	memcpy(&(DArrayPtr->Payload[DArrayPtr->EntriesUsed]), PayloadPtr, sizeof(double));

	DArrayPtr->EntriesUsed++;

	return(DArrayPtr->EntriesUsed - 1);
}

/**************************************************************************
* DestroyDArray
*   Frees memory used by Data and resets state of the Dynamic Array
*   by setting to zero Capacity and ElementsUsed
**************************************************************************/
void DestroyDArray( DArray *DArrayPtr ){
	/* Zero the properties of the array */
	DArrayPtr->EntriesUsed = 0;
	DArrayPtr->Capacity = 0;

	/* Free the memory and ground it */
	free(DArrayPtr->Payload);
	DArrayPtr->Payload = NULL;
}

void PrintArray(DArray *DArrayPtr){
	int lcv;

	for(lcv = 0; lcv < DArrayPtr->EntriesUsed; lcv++){
		fprintf(stdout, " %f \n", DArrayPtr->Payload[lcv]);
	}


}



