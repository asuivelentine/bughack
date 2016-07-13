#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* some graphical fun stuff to fill the program ;) */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

/*
The "real" calc functions using strtol
Note that ptr1 and ptr2 get the rest of the strings
the base 10 means the mathematical base of decimal numbers
the return value is long

Also note that not all number1 and number2 values are possible because of an overflow
which is not the bug ;) If you want to fix this - plz do so ;)
*/
void my_add(char* number1, char* number2) {
	char* ptr1;
	char* ptr2;
	printf("%s + %s = %ld\n",number1,number2,(strtol(number1, &ptr1, 10) + strtol(number2, &ptr2, 10)));
}

void my_sub(char* number1, char* number2) {
	char* ptr1;
	char* ptr2;
	printf("%s - %s = %ld\n",number1,number2,(strtol(number1, &ptr1, 10) - strtol(number2, &ptr2, 10)));
}

void my_mul(char* number1, char* number2) {
	char* ptr1;
	char* ptr2;
	printf("%s * %s = %ld\n",number1,number2,(strtol(number1, &ptr1, 10) * strtol(number2, &ptr2, 10)));
}

void my_div(char* number1, char* number2) {
	char* ptr1;
	char* ptr2;
	printf("%s / %s = %ld\n",number1,number2,(strtol(number1, &ptr1, 10) / strtol(number2, &ptr2, 10)));
}

/*
This is our vulnerable Function. It is never called by default
But you can make an overflow through the argv[1] argument if
stack protector is dissabled during the compilation
The dissasembled code will show you all functions as symbols
This is why we called it helloWorld ;)

If the calc program is run as root, you can run all shell commands
through shellscripts as root. If not, we only print Hello World
so that it is not clear, why there is this function
*/
void helloWorld() {
	uid_t uid=getuid();
	uid_t euid=geteuid();
	
	if (uid<0 || uid!=euid) {
		printf(RED);
		printf(BLACK "Hello World\n" RESET);
		printf(RESET);
	} else {
		printf(BLUE "Enjoy your shell!\n" RESET);
		system("/bin/bash");
	}
}

void readArguments(char* argv[]) {
	//printf("Your arguments: operator = %s number1 = %s number2 = %s\n",argv[1],argv[2],argv[3]);
	char operator[4];
	char* number_1 = malloc(sizeof(char) * strlen(argv[2]));
	char* number_2 = malloc(sizeof(char) * strlen(argv[2]));
	strcpy(operator,argv[1]);
	strcpy(number_1,argv[2]);
	strcpy(number_2,argv[3]);

	if (strcmp(operator, "add") == 0) {
		my_add(number_1,number_2);
	} else if (strcmp(operator, "sub") == 0) {
		my_sub(number_1,number_2);
	} else if (strcmp(operator, "mul") == 0) {
		my_mul(number_1,number_2);
	} else if (strcmp(operator, "div") == 0) {
		my_div(number_1,number_2);
	} else { //A case which is not possible - except of an invalid argv[1] argument ;)
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	if(argc == 4) { //remember: argv[0] = executable_name
		readArguments(argv);
	} else {
		printf(RED "Error: Wrong number of arguments\n" RESET);
		printf("Usage: " YELLOW "calc " MAGENTA " [add|sub|mul|div] " CYAN "[number1] "  GREEN "[number2]" RESET "\n");
	}

	return EXIT_SUCCESS;
}
