#ifndef SALT_H
#define SALT_H

// Struct Ion for bedakan tipe ion
typedef struct Ion {
    char formula[10];
    int charge;
    char type; // 'K' untuk kation, 'A' untuk anion
} Ion;

// Struct salt for nyimpan informasi garam
typedef struct Salt {
    char name[30];
    Ion cation;
    Ion anion;
    char formula[20];
    struct Salt* next;
} Salt;

// Function prototypes interface
Salt* create_salt(const char* name, const char* cation, int cat_charge, 
                 const char* anion, int an_charge);
void add_salt(Salt** salt_list, Salt* new_salt);
Salt* find_salt(Salt* salt_list, const char* name);
void print_salts(Salt* salt_list);
void read_salts_from_file(Salt** salt_list, const char* filename);
void free_salt_list(Salt* salt_list);


#endif