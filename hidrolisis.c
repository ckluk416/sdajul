#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hidrolisis.h"

// Anda boleh perluas detection ini sesuai database Anda
int is_strong_base_cation(const char* cat) {
    return (strcmp(cat, "Na") == 0 || strcmp(cat, "K") == 0 || strcmp(cat, "Li") == 0 || strcmp(cat, "Ca") == 0 || strcmp(cat, "Ba") == 0);
}
int is_strong_acid_anion(const char* an) {
    return (strcmp(an, "Cl") == 0 || strcmp(an, "Br") == 0 || strcmp(an, "I") == 0 ||
            strcmp(an, "NO3") == 0 || strcmp(an, "SO4") == 0 || strcmp(an, "ClO4") == 0);
}