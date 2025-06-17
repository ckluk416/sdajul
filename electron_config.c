#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "electron_config.h"

OrbitalNode *create_orbital_node(const char *name, int max_e, int current_e, int energy){
    OrbitalNode *node = (OrbitalNode *)malloc(sizeof(OrbitalNode));
    if(!node){
        printf("error: tidak dapat mengalokasikan memori untuk node orbital\n");
        exit(EXIT_FAILURE);
    }
    strncpy(node->orbital_name, name, sizeof(node->orbital_name) - 1);
    node->orbital_name[sizeof(node->orbital_name) - 1] = '\0';
    node->max_electrons = max_e;
    node->current_electrons = current_e;
    node->energy_level = energy;
    node->left = node->right = NULL;
    return node;
}

// Build orbital tree berdasarkan urutan pengisian elektron sederhana (Hingga 6s)
OrbitalNode* build_electron_config(int atomic_number) {
    // Daftar minimal urutan pengisian orbital
    const char* order[] = {"1s", "2s", "2p", "3s", "3p", "4s", "3d", "4p", "5s", "4d", "5p", "6s"};
    const int max_e[] = {2, 2, 6, 2, 6, 2, 10, 6, 2, 10, 6, 2};
    const int levels[] = {1, 2, 2, 3, 3, 4, 3, 4, 5, 4, 5, 6};
    OrbitalNode* root = NULL;
    OrbitalNode* last = NULL;
    int electrons_left = atomic_number;
    int orbital_count = sizeof(order) / sizeof(order[0]);
    for (int i = 0; i < orbital_count && electrons_left > 0; i++) {
        int electrons_in_orbital = electrons_left > max_e[i] ? max_e[i] : electrons_left;
        OrbitalNode* new_node = create_orbital_node(order[i], max_e[i], electrons_in_orbital, levels[i]);
        if (!root) root = new_node;
        else last->right = new_node; 
        last = new_node;
        electrons_left -= electrons_in_orbital;
    }
    return root;
}

void print_orbital_tree(const OrbitalNode* root, const char* prefix, int is_last) {
    if (root != NULL) {
        printf("%s", prefix);
        printf(is_last ? "└── " : "├── ");

        printf("%s: ", root->orbital_name);
        for (int i = 0; i < root->current_electrons; i++)
            printf("↑↓");
        for (int i = root->current_electrons; i < root->max_electrons; i++)
            printf("__");
        printf(" (%d/%d electrons)\n", root->current_electrons, root->max_electrons);

        char new_prefix[100];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

        int child_count = (root->left != NULL) + (root->right != NULL);
        int child_index = 0;

        if (root->left)
            print_orbital_tree(root->left, new_prefix, ++child_index == child_count);
        if (root->right)
            print_orbital_tree(root->right, new_prefix, ++child_index == child_count);
    }
}


// Tampilkan konfigurasi elektron (string)
void display_electron_config(int atomic_number) {
    const char* order[] = {"1s", "2s", "2p", "3s", "3p", "4s", "3d", "4p", "5s", "4d", "5p", "6s"};
    const int max_e[] = {2, 2, 6, 2, 6, 2, 10, 6, 2, 10, 6, 2};
    int electrons_left = atomic_number;
    int orbital_count = sizeof(order) / sizeof(order[0]);
    printf("Electron config: ");
    for (int i = 0; i < orbital_count && electrons_left > 0; i++) {
        int electrons_in_orbital = electrons_left > max_e[i] ? max_e[i] : electrons_left;
        printf("%s^%d ", order[i], electrons_in_orbital);
        electrons_left -= electrons_in_orbital;
    }
    printf("\n");
}

void free_orbital_tree(OrbitalNode* root) {
    while (root) {
        OrbitalNode* tmp = root;
        root = root->right;
        free(tmp);
    }
}