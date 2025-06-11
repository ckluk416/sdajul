#include "chem_tree.h"
#include <string.h>
#include <stdlib.h>

// Deklarasi 2 tree secara global to make it always empty 
TreeNode* periodic_tree_by_atomic = NULL;
TreeNode* periodic_tree_by_name = NULL;

// Fungsi perbandingan
int compare_by_atomic_number(const Element* a, const Element* b) {
    return a->atomic_number - b->atomic_number;
}

int compare_by_name(const Element* a, const Element* b) {
    return strcmp(a->name, b->name);
}