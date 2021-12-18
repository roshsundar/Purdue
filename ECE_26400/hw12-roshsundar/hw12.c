#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}

	float result; //store the result of your calculation here.
	
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */
	popResult res = RPN(argv[1]);

	if (res.good == false)
	{
		return EXIT_FAILURE;
	}

	result = res.value;
	printf("%f\n", result);
	
	return EXIT_SUCCESS;
}
