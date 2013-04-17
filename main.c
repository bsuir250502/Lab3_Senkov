#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

#define STR_MAX 256

typedef struct information {
    char name[STR_MAX];
    char main_info[STR_MAX];
    struct information *next;
} information_t;

typedef struct ring {
    information_t *first;
    information_t *last;
} ring_t;

/* function from lib1.h */
void str_input(char *information, char *input_text, int max_number_of_symbols);
int int_input(char *information, int Min, int Max);
void help_output();

void help(int argc, char **argv);
int select_input(ring_t junction_point, int elements_number);
void list_output();
int manual_input(ring_t junction_point, int elements_number);
int add_element(int elements_number);

int main(int argc, char **argv)
{
    ring_t junction_point;
    int elements_number = 0;
    junction_point.first = NULL;
    junction_point.last = NULL;
    help(argc,argv);
    elements_number = select_input(junction_point, elements_number);
    puts ("\n3 lab.");
    return 0;
}

void help(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        help_output();
        exit(0);
    }
}

int select_input(ring_t junction_point, int elements_number)
{
    int select;
    puts ("\nInfo input about appliances :\n"
          "    1) view already done appliances list. \n"
          "    2) manual input. (name, brief info) ");
    select = int_input("enter", 1, 2);
    if (select == 1) {
        list_output();
        return 1;
    }
    else {
        return manual_input(junction_point, elements_number);
    }

}

void list_output()
{
    char buffer[STR_MAX];
    FILE *file = fopen ("info.txt","r");
    while (fgets(buffer, sizeof(buffer)/sizeof(*buffer), file)) {
        printf ("%s",buffer);
    }
    fclose (file);
}

int manual_input(ring_t junction_point, int elements_number)
{   
    puts ("\nEnter info about appliances('stop' for input end):"); 
    while (add_element(elements_number)) {
        elements_number ++;
        /*printf ("");*/      
    }
    return elements_number;
}

int add_element(int elements_number)
{
    information_t *new_element;
    new_element = (information_t*)malloc(sizeof(*new_element));
    printf ("%d)",elements_number + 1);
    str_input("name:", new_element->name, STR_MAX);
    if (!strcmp(new_element->name, "stop")) {
        return 0;
    }
    return 1;
} 