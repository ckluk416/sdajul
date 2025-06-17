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

// Hidrolisis interaktif dengan database Ka/Kb lookup
void hidrolisis_process(const Salt* salt_list, const char* nama_garam, Stack* history, Queue* q, const KaKbEntry* db, int ndb) {
    const Salt* s = salt_list;
    while (s) {
        if (strcmp(s->name, nama_garam) == 0)
            break;
        s = s->next;
    }
    if (!s) {
        printf("Garam tidak ditemukan!\n");
        push_operation(history, "Hidrolisis Garam (gagal)");
        enqueue_process(q, "Hidrolisis Garam (gagal)");
        return;
    }

    printf("\n=== Analisis Hidrolisis ===\n");
    printf("Nama: %s\nRumus: %s\nKation: %s (%d)\nAnion: %s (%d)\n",
           s->name, s->formula, s->cation.formula, s->cation.charge, s->anion.formula, s->anion.charge);

    int strong_cation = is_strong_base_cation(s->cation.formula);
    int strong_anion = is_strong_acid_anion(s->anion.formula);

    printf("Ionisasi: %s → %s^%+d + %s^%+d\n", s->formula, s->cation.formula, s->cation.charge, s->anion.formula, s->anion.charge);

    if (strong_cation && strong_anion) {
        printf("Tipe: Garam dari asam kuat dan basa kuat\n");
        printf("Hidrolisis: Tidak, larutan bersifat netral (pH = 7)\n");
    } else if (strong_cation && !strong_anion) {
        printf("Tipe: Garam dari basa kuat dan asam lemah\n");
        printf("Hidrolisis: Anion menghidrolisis air\n");
        printf("Reaksi: %s^- + H2O ⇌ H%s + OH^-\n", s->anion.formula, s->anion.formula);
        printf("Larutan bersifat basa (pH > 7)\n");
        char jawab[10];
        printf("Hitung pH hidrolisis? (y/n): "); fgets(jawab, sizeof(jawab), stdin);
        if (tolower(jawab[0]) == 'y') {
            double c = 0;
            printf("Masukkan konsentrasi garam (M): "); scanf("%lf", &c); getchar();
            // Lookup Ka dari database
            double Ka = lookup_kakb(db, ndb, "Asam", s->anion.formula, NULL);
            if (Ka == 0.0) {
                printf("Ka tidak ditemukan di database, masukkan manual: "); scanf("%lf", &Ka); getchar();
            } else {
                printf("Ditemukan Ka = %g\n", Ka);
            }
            double Kb = 1e-14 / Ka;
            double OH = sqrt(Kb * c);
            double pOH = -log10(OH);
            double pH = 14 - pOH;
            printf("pH larutan: %.2f\n", pH);
        }
    } else if (!strong_cation && strong_anion) {
        printf("Tipe: Garam dari basa lemah dan asam kuat\n");
        printf("Hidrolisis: Kation menghidrolisis air\n");
        printf("Reaksi: %s^+ + H2O ⇌ %sOH + H^+\n", s->cation.formula, s->cation.formula);
        printf("Larutan bersifat asam (pH < 7)\n");
        char jawab[10];
        printf("Hitung pH hidrolisis? (y/n): "); fgets(jawab, sizeof(jawab), stdin);
        if (tolower(jawab[0]) == 'y') {
            double c = 0;
            printf("Masukkan konsentrasi garam (M): "); scanf("%lf", &c); getchar();
            // Lookup Kb dari database
            double Kb = lookup_kakb(db, ndb, "Basa", s->cation.formula, NULL);
            if (Kb == 0.0) {
                printf("Kb tidak ditemukan di database, masukkan manual: "); scanf("%lf", &Kb); getchar();
            } else {
                printf("Ditemukan Kb = %g\n", Kb);
            }
            double Ka = 1e-14 / Kb;
            double H = sqrt(Ka * c);
            double pH = -log10(H);
            printf("pH larutan: %.2f\n", pH);
        }
    } else {
        printf("Tipe: Garam dari asam lemah dan basa lemah\n");
        printf("Hidrolisis: Kation dan anion keduanya menghidrolisis air\n");
        printf("Larutan bersifat asam/basa/atau netral tergantung Ka & Kb\n");
        char jawab[10];
        printf("Hitung pH hidrolisis? (y/n): "); fgets(jawab, sizeof(jawab), stdin);
        if (tolower(jawab[0]) == 'y') {
            double c = 0;
            printf("Masukkan konsentrasi garam (M): "); scanf("%lf", &c); getchar();
            double Ka = lookup_kakb(db, ndb, "Asam", s->anion.formula, NULL);
            if (Ka == 0.0) { printf("Ka tidak ditemukan di database, masukkan manual: "); scanf("%lf", &Ka); getchar(); }
            else printf("Ditemukan Ka = %g\n", Ka);
            double Kb = lookup_kakb(db, ndb, "Basa", s->cation.formula, NULL);
            if (Kb == 0.0) { printf("Kb tidak ditemukan di database, masukkan manual: "); scanf("%lf", &Kb); getchar(); }
            else printf("Ditemukan Kb = %g\n", Kb);
            double H = sqrt((Ka * 1e-14 / Kb) * c);
            double pH = -log10(H);
            printf("pH larutan (pendekatan): %.2f\n", pH);
        }
    }
    push_operation(history, "Hidrolisis Garam");
    enqueue_process(q, "Hidrolisis Garam");
}