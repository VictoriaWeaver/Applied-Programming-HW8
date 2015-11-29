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

		}
		/* Check for -e use case */
		else if((4 == argc) && (0 == strcmp(argv[1],"-e"))){

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
