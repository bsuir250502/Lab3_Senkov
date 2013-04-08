#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

#define MAX_NUMBER_OF_SYMBL 256

typedef struct information {
	char name[MAX_NUMBER_OF_SYMBL];
	char main_info[MAX_NUMBER_OF_SYMBL];
	information *next;
} information_t;

typedef struct control {
	information_t *first;
	information_t *last;
} control_t;

/* function from lib1.h */
void help_output();


int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        help_output();
        return 0;
    }
    puts ("3 lab.");
    return 0;
}

