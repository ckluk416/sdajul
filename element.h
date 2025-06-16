#ifndef ELEMENT_H
#define ELEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//modul
void init_periodic_table_from_file(Element* table, int* count, const char* filename); //untuk inisasialisasi tabel periodik dari file
Element* search_by_symbol(Element* table, int count, char* symbol); //untuk menari elemen berdasarkan simbol
void print_element(const Element* elem); //untuk mencetak info elemen

#endif