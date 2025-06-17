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

void free_orbital_tree(OrbitalNode* root) {
    while (root) {
        OrbitalNode* tmp = root;
        root = root->right;
        free(tmp);
    }
}