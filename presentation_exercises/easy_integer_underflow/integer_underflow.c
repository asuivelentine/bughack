#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[20];
    int i = atoi(argv[1]);
    if (i > 20) {
        return EXIT_FAILURE;
    }
    memcpy(buffer, argv[2], i*sizeof(int));

    printf("the number %d = %lu bytes\n", i, i*sizeof(int));
    printf("the buffer is = %s\n", buffer);
    printf("Zahl: %s", (char *) &i);

    return EXIT_SUCCESS;
}
