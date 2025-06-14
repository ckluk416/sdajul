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

// Struct SaltList untuk nyimpen list garam
typedef struct SaltList {
    Salt* head;
    Salt* tail;
    int count;
} SaltList;

// Function prototypes interface
Salt* create_salt(const char* name, const char* cation, int cat_charge, 
                 const char* anion, int an_charge); //buat garam baru
void add_salt(Salt* new_salt);//tambah garam ke list
Salt* find_salt(Salt* salt_list, const char* name);//cari garam berdasarkan nama
void print_salts(Salt* salt_list); //print semua garam
void read_salts_from_file(Salt** salt_list, const char* filename); //read garam dari file
void free_salt_list(Salt* salt_list);//dealloc memori list garam

// Function about salt list
SaltList* create_salt_list();

//error handling
typedef enum {
    SALT_SUCCESS,
    SALT_NULL_POINTER,
} SaltResult;

#endif