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