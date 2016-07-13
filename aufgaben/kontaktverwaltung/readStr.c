#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kontakt.h"
#include "menu.h"
#include "functions.h"
#include "readStr.h"
#include "replaceStr.h"
#include "dbLaden.h"
#include "dbSpeichern.h"
#include "main.h"

int input(char *s,int length);

char* readStr() {
    char *buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if(buffer == NULL) {
        perror("Unable to allocate buffer");
        exit(1);
    }

    characters = getline(&buffer,&bufsize,stdin);
    //printf("%zu Zeichen wurden gelesen.\n",characters);
    
    return buffer;
}
