#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_ph.h"

// Load database Ka/Kb dari file CSV
int load_kakb_database(const char* filename, KaKbEntry* db, int* ndb) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Gagal membuka database KaKb: %s\n", filename);
        *ndb = 0;
        return 0;
    }
    char line[128];
    int count = 0;
    fgets(line, sizeof(line), f); // Skip header
    while (fgets(line, sizeof(line), f)) {
        char* token = strtok(line, ",");
        if (!token) break;
        strncpy(db[count].tipe, token, sizeof(db[count].tipe) - 1);

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(db[count].nama, token, sizeof(db[count].nama) - 1);

        token = strtok(NULL, ",");
        if (!token) break;
        strncpy(db[count].formula, token, sizeof(db[count].formula) - 1);

        token = strtok(NULL, ",");
        if (!token) break;
        db[count].tetapan = atof(token);

        count++;
        if (count >= MAX_DB_PH) break;
    }
    fclose(f);
    *ndb = count;
    return 1;
}

// Lookup Ka/Kb berdasarkan tipe (Asam/Basa), formula, atau nama
double lookup_kakb(const KaKbEntry* db, int ndb, const char* tipe, const char* formula, const char* nama) {
    for (int i = 0; i < ndb; i++) {
        // Perbandingan tipe (case-insensitive)
        if (strcasecmp(db[i].tipe, tipe) != 0) continue;

        // Hapus newline di formula database jika ada
        char db_formula[32];
        strncpy(db_formula, db[i].formula, sizeof(db_formula));
        db_formula[sizeof(db_formula)-1] = 0;
        db_formula[strcspn(db_formula, "\r\n")] = 0;

        // Perbandingan formula/nama (case-insensitive)
        if ((formula && strlen(formula) && strcasecmp(db_formula, formula) == 0) ||
            (nama && strlen(nama) && strcasecmp(db[i].nama, nama) == 0))
            return db[i].tetapan;
    }
    return 0.0;
}