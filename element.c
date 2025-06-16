#include "element.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Element periodic_table[118];
int element_count = 0;

void init_periodic_table_from_file(Element *table, int *count, const char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        fprintf(stderr, "error: tidak dapat membuka file %s\n", filename);
    }

    *count = 0;
    while(fscanf(file, "%d %s %s %f %d %d %s %s %f %[^\n]",
                  &table[*count].atomic_number,
                  table[*count].symbol,
                  table[*count].name,
                  &table[*count].atomic_weight,
                  &table[*count].period,
                  &table[*count].group,
                  table[*count].electron_config,
                  table[*count].category,
                  &table[*count].electronegativity,
                  table[*count].oxidation_states) == 10) {
        (*count)++;
        if (*count >= 118) {
            break;
        }
    } 
    fclose(file);
}
