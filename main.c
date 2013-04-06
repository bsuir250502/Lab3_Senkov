#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

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

