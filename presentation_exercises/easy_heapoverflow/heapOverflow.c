#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void heapOverflow(char* argv[]) {
	long diff;
	char* var1;
	char* var2;
	var1 = (char *) malloc(sizeof(char)*5);
	var2 = (char *) malloc(sizeof(char)*4);
	
	if(var1 == NULL || var2 == NULL) {
		fprintf(stdout,"couldn´t allocate memory on the heap");
		exit(EXIT_FAILURE);
	}

	diff = (long)var2 - (long)var1;
	printf("var1 = %p & var2 = %p & diff %lu\n",var1,var2,diff);
	strcpy(var2,"test");
	printf("BEFORE: var2 = %s\n",var2);
	strcpy(var1,argv[1]);
	printf("AFTER:  var2 = %s\n",var2);
}

int main(int argc, char* argv[]) {
	heapOverflow(argv);
	return EXIT_SUCCESS;
}
