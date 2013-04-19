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

void str_input(char *information, char *input_text, int max_number_of_symbols);
int int_input(char *information, int Min, int Max);
void help(int argc, char **argv);
void file_output(char *file_name);
int administration(ring_t point);
int select_info_variant();
void manual_input_output(ring_t point);
int add_element(ring_t *point);
void output_of_order(char *which, ring_t *point, int elements_number);
void inverse(ring_t *point, int elements_number);

int main(int argc, char **argv)
{
    ring_t point;
    point.first = NULL;
    point.last = NULL;

    help(argc,argv);
    administration(point);
    return 0;
}

void help(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        exit(0);
    }
}

void file_output(char *file_name)
{   
    char input_buffer[STR_MAX];
    FILE *file;
    if (!strcmp(file_name, "README.txt")) {
        file = fopen("README.txt","r") ;
    }
    else if (!strcmp(file_name, "info.txt")) {
        file = fopen("info.txt","r") ;
    }
    while (fgets(input_buffer, sizeof(input_buffer)/sizeof(*input_buffer), file)) {
            printf ("%s", input_buffer);
        }
    fclose(file);
    puts("\n");
}

int administration(ring_t point)
{
    int i = 0;
    do {
        if (select_info_variant(point) == 1) {
            file_output("info.txt");
            puts("                          If you want:\n"
                 "              -----------------------------------\n"
                 "                    1) to continue, enter '1'\n"
                 "              -----------------------------------\n"
                 "              2) to close this prigram, enter '2'\n");
            i = int_input("enter", 1, 2);
            if (i == 2) {
                exit(0);
            }
        }
        else {
            manual_input_output(point);
            return 1;
        } 
    } while(i == 1);
    return 1;
}

int select_info_variant()
{
    int select;
    puts ("\n                 Info input about appliances :\n"
          "             ---------------------------------------\n"
          "              1) view already done appliances list. \n"
          "             ---------------------------------------\n"
          "              2) manual input. (name, brief info) \n");
    select = int_input("enter", 1, 2);
    return select;
}

void manual_input_output(ring_t point)
{
    int elements_number = 0;
    puts ("\n-----   Enter info about appliances('stop' for input end):   -----\n");
          printf ("%d)",elements_number + 1);  
    while (add_element(&point)) {
        elements_number ++;
        printf ("%d)",elements_number + 1);  
    } 
    point.last->next = point.first;
    output_of_order("first", &point, elements_number);
    inverse(&point, elements_number);




    output_of_order("inverse", &point, elements_number);
}

int add_element(ring_t *point)
{
    information_t *new_element;
    new_element = (information_t*)malloc(sizeof(new_element));
    new_element->next = NULL;
    str_input(" name: ", new_element->name, STR_MAX);
    if (!strcmp(new_element->name, "stop")) {
        return 0;
    }
    str_input("   main information: ", new_element->main_info, STR_MAX);
    if (point->first == NULL) {
        point->first = new_element;
    }
    else {
        point->last->next = new_element;
    }
    point->last = new_element;
    return 1;
} 

void inverse(ring_t *point, int elements_number) 
{   int i,j;
    information_t *info;
    information_t *element;
    info = point->last;
    for (i = elements_number -2; i >0  ; i--) {
        element = point->first;
        for (j = 0; j < i; j++) {
            element = element->next;
        }       
        point->last->next = element;
        point->last = element;
    }
    point->last->next = point->first;
    point->last = point->first;
    point->first = info;
    point->last->next = point->first;
}

void output_of_order(char *which, ring_t *point, int elements_number)
{
    int i;
    information_t *info;
    info=point->first; 
    printf ("\n----------   Info output in %s order:   ----------\n", which);
    for(i = 0; i < elements_number; i++) {
        printf ("%d) name: %s\n   main info:%s\n",
                 i + 1, info->name, info->main_info);
        info = info->next;
    }
}
