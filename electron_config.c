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