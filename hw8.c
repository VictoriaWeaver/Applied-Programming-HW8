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
#include "Dynamic.h"


int main(int argc, char *argv[]){
	/* Check if proper amount of commandline arguments */
	if(1 >= argc){

		/* Check for first 3 usage cases */
		if((3 == argc) && ((0 == strcmp(argv[1], "-nak")) ||  (0 == strcmp(argv[1], "-nat")) || (0 == strcmp(argv[1], "-cl")))){

			/* Declare pointer to file object */
			FILE *inputFile;

			/* Attempt to open the input file */
			inputFile = fopen(argv[2], "r");

			/* Check if opened properly */
			if(NULL == inputFile){

				fprintf(stdout, "\nFile was not opened properly!\n");
				return 2;

			}
			else{
				double dA, dB;			/* The first line in the file should be the derivatives */
				Points data;			/* Data points */
				Csplines splines;		/* Splines */
				double xpoint, ypoint;	/* Data read in */

				/* Read in the data using dynamic arrays */



			}


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

				fprintf(stdout, "\nFiles were not opened properly!\n");
				return 2;

			}
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
