#ifndef DB_PH_H
#define DB_PH_H

#define MAX_DB_PH 32

typedef struct {
    char tipe[8];      // "Asam" atau "Basa"
    char nama[32];     // Nama lengkap
    char formula[16];  // Rumus
    double tetapan;    // Ka atau Kb
} KaKbEntry;


#endif