#ifndef ELECTRON_CONFIG_H
#define ELECTRON_CONFIG_H

typedef struct OrbitalNode {
    char orbital_name[4];
    int max_electrons;
    int current_electrons;
    int energy_level;
    struct OrbitalNode* left;
    struct OrbitalNode* right;
} OrbitalNode;

// Function prototypes interface
OrbitalNode* create_orbital_node(const char* name, int max_e, int current_e, int energy);
void print_orbital_tree(const OrbitalNode* root, const char* prefix, int is_last);
OrbitalNode* build_electron_config(int atomic_number);
void display_electron_config(int atomic_number);
void free_orbital_tree(OrbitalNode* root);

#endif