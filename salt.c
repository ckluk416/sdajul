#include "salt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Salt *create_salt(const char *name, const char *cation, int cat_charge, const char *anion, int an_charge){
    Salt *new_salt = (Salt *)malloc(sizeof(Salt)); //alokasi memori u/ new_salt
    strcpy(new_salt->name, name); //salin nama garam
    //salin kation
    strcpy(new_salt->cation.formula, cation); //salin rumus kation
    new_salt->cation.charge = cat_charge; //salin muatan kation
    new_salt->cation.type = 'K'; //set tipe kation
    // salin anion
    strcpy(new_salt->anion.formula, anion); //salin rmus anion
    new_salt->anion.charge = an_charge;//salin muatan anion
    new_salt->anion.type = 'A';//set tipe anion
    //generate rumus garam 
    int cat_abs = abs(cat_charge); //ambil nilai absolut muatan kation 
    int an_abs = abs(an_charge); //ambil nilai absolut muatan anion
    int gcd = 1; //inisialisasi gcd (greatest common divisor)
    //mencari gcd dari muatan kation dan anion
    for(int i = 1; i <= cat_abs && i <= an_abs; i++){ 
        if(cat_abs % i == 0 && an_abs % i == 0){
            gcd = i;
        }
    }
    //menghitung koefisien kation dan anion
    int cat_coeff = an_abs / gcd; 
    int an_coeff = cat_abs / gcd;
    //mmbuat rumus garam berdasarkan koefisien kation dan anion
    if(cat_coeff == 1){ 
        if(an_coeff == 1){
            sprintf(new_salt->formula, "%s%s", cation, anion);
        } else{
            sprintf(new_salt->formula, "%s(%s)%d", cation, anion, an_coeff);
        }
    } else{
        if(an_coeff == 1){
            sprintf(new_salt->formula, "(%s)%d%s", cation, cat_coeff, anion);
        } else{
            sprintf(new_salt->formula, "(%s)%d(%s)%d", cation, cat_coeff, anion, an_coeff);
        }
    }

    new_salt->next = NULL; 
    return new_salt;
}

// Add Salt to linked list
void add_salt(Salt** salt_list, Salt* new_salt) {
    if (*salt_list == NULL) {
        *salt_list = new_salt;
    } else {
        Salt* current = *salt_list;
        while (current->next != NULL)
            current = current->next;
        current->next = new_salt;
    }
}

// Find Salt by name
Salt* find_salt(Salt* salt_list, const char* name) {
    Salt* current = salt_list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}


