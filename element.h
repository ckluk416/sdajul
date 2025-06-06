#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct Element {
    int atomic_number;
    char symbol[4];
    char name[20];
    float atomic_weight;
    int period;
    int group;
    char electron_config[20];
    char category[20];
    float electronegativity;
    char oxidation_states[50];
} Element;

// Function prototypes interface
Element* search_by_symbol(Element* table, int count, char* symbol);
void print_element(Element* elem);
void init_periodic_table_from_file(Element* table, int* count, const char* filename);

#endif