#include <stdio.h>

int main(void){
	double x;
	x = 0.0;
	
	while(x < 3.14125){
		fprintf(stdout, "%f\n", x);
		x = x + 0.00125;
	}

	return 0;
}
