/************************************************************************
* Victoria Weaver
* vew4644@rit.edu
*
* Homework 8, Driver program for cubic splines implementations.
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "DynamicArrays.h"


int main(int argc, char *argv[]){
	/* Check if proper amount of commandline arguments */
	if(1 <= argc){

		/* Check for first 3 usage cases */
		if((3 == argc) && ((0 == strcmp(argv[1], "-nak")) ||  (0 == strcmp(argv[1], "-nat")) || (0 == strcmp(argv[1], "-cl")))){


			/* Declare pointer to file object */
			FILE *inputFile;

			/* Attempt to open the input file */
			inputFile = fopen(argv[2], "r");

			/* Check if opened properly */
			if(NULL == inputFile){

				fprintf(stdout, "File was not opened properly!\n");
				return 2;

			}
			else{
				double dA, dB;			/* The first line in the file should be the derivatives */
				Points data;			/* Data points */
				CSplines splines;		/* Splines */
				double xpoint, ypoint;	/* Data read in */

				
				/* Create a Dynamic Array to read in the X data and one for the Y data */
				DArray XArray;
				DArray YArray;

				int lcv;

				/* Initial Size of 100 */	
				CreateDArray(&XArray, 100);

				/* Initial Size of 100 */	
				CreateDArray(&YArray, 100);


				/* Read in the data using dynamic arrays */

				/* Scan the first two values for deriv at A and B */
				fscanf(inputFile, "%lf %lf", &dA, &dB);

				while(fscanf(inputFile, "%lf %lf", &xpoint, &ypoint)!=EOF){

					PushToDArray(&XArray, &xpoint);
					PushToDArray(&YArray, &ypoint);

				}


				/* Create the points and splines */
				p_alloc(&data, XArray.EntriesUsed);
				s_alloc(&splines, (XArray.EntriesUsed-1));

				memcpy(data.X, XArray.Payload, (data.N)*sizeof(double));
				memcpy(data.Y, YArray.Payload, (data.N)*sizeof(double));

				data.y0 = dA;
				data.yn = dB;

				memcpy(splines.X, XArray.Payload, (data.N)*sizeof(double));


				/* not-a-knot splines method */
				if(0 == strcmp(argv[1], "-nak")){

					fprintf(stdout, "not-a-knot method: \n");

					cspline_nak(&data, &splines);
					printSplines(&splines);
				}

				/* natural splines method */
				if(0 == strcmp(argv[1],"-nat")){

					fprintf(stdout, "natural method: \n");

					cspline_natural(&data, &splines);
					printSplines(&splines);
				}

				/* clamped splines method */
				if(0 == strcmp(argv[1],"-cl")){

					fprintf(stdout, "clamped method: \n");

					cspline_clamped(&data, dA, dB, &splines); 
					printSplines(&splines);
				}

				/* Free the data and spline structures */
				s_free(&splines);
				p_free(&data);


				/* Free the DArray */
				DestroyDArray(&XArray);
				DestroyDArray(&YArray);


			}

			fclose(inputFile);

		}
		/* Check for -e use case */
		else if((4 == argc) && (0 == strcmp(argv[1],"-e"))){
			/* Declare pointer to file object */
			FILE *splineFile, *evalFile;

			/* Attempt to open the files */
			splineFile = fopen(argv[2], "r");
			evalFile = fopen(argv[2], "r");

			/* Check if opened properly */
			if((NULL == splineFile) || (NULL == evalFile)){

				fprintf(stdout, "Files were not opened properly!\n");
				return 2;

			}
			else{
				/* Declare variables to be read from sparameters file */
				double X0, X1, a, b, c, d;

				/* Create a Dynamic Array to read in the data */
				DArray *DArrayPtr;

				DArrayPtr = NULL;

				/* Initial Size of 100 */	
				CreateDArray(DArrayPtr, 100);



				/* the splines to standard out 
            	of the form:  X0 X1 d c b a */


				/* Free the DArray */
				DestroyDArray(DArrayPtr);
 

			}

			fclose(splineFile);
			fclose(evalFile);

		}
		else{
			/* Print usage message */
			fprintf(stdout, "Usage: ./hw8 <-nak, -nat, -cl> data.txt \nUsage: ./hw8 -e sparameters.txt eval.txt\n");	
		}

	}
	else{
		/* Print usage message */
		fprintf(stdout, "Usage: ./hw8 <-nak, -nat, -cl> data.txt \nUsage: ./hw8 -e sparameters.txt eval.txt\n");
	}
}
