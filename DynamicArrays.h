/**************************************************************************
* Dynamic Arrays Module  - public interface
*
* data types: Data - struct with data to be stored
*             DArray - structure for Dynamic Array Header
*
* functions: CreateDArray, PushToDArray, DestroyDArray
*
* Author: Greg Semeraro, Juan C. Cockburn
* Revised: JCCK 2/3/2015
**************************************************************************/
#ifndef _DYNAMIC_ARRAYS_H_
#define _DYNAMIC_ARRAYS_H_

/**************************  modify as needed *************************/
/** Data typemark to store payload: Modify according to application  ***/
/** In this case the payload consists of a sequence number and a word **/
/*typedef struct {
   int Num;            Sequence number 
   char String[256];   word, (less than 255 chars -not checked!) 
  } Data;*/
/************ Nothing else in the module needs to be modified **********/

/* Growth Policy : Constant Size */
#define GROWTH_AMOUNT (100)  

/************ Nothing else in the module needs to be modified **********/

/**************************************************************************
* DArray - Dynamic Array Header structure to keep track of its "state" 
*          The "state" of the Dynamic Array is: Capacity and EntriesUsed
**************************************************************************/
typedef struct DArray {
   unsigned int Capacity;    /* Max Number of elements array can hold */
   unsigned int EntriesUsed; /* Number of array elements "used"       */
   double *Payload;   /* Pointer to array that actually holds the data  */
  } DArray;

/**************************************************************************
* CreateDArray 
*   Allocates memory and initializes DArray with specified initial size.
**************************************************************************/
void CreateDArray( DArray *DArrayPtr, unsigned int InitialSize );

/**************************************************************************
* PushToDArray
* Adds data to the end (push) of dynamic array and updates ElementsUsed 
*   If full, realocates memory space according to growth policy
* postcond: returns the index to the last element added 
**************************************************************************/
unsigned int PushToDArray( DArray *DArrayPtr, double *PayloadPtr );

/**************************************************************************
* DestroyDArray
*   Frees memory used by Data and resets state of the Dynamic Array
*   by setting to zero Capacity and ElementsUsed
**************************************************************************/
void DestroyDArray(DArray *DArrayPtr);


void PrintArray(DArray *DArrayPtr);

#endif /* _DYNAMIC_ARRAYS_H_ */
