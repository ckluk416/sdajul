#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "element.h"
#include "chem_tree.h"
#include "salt.h"
#include "stack.h"
#include "queue.h"
#include "electron_config.h"
#include "hidrolisis.h"
#include "db_ph.h"

#include "run.h"

#define ELEMENT_FILE "tabel_Periodik.txt"
#define SALT_FILE "Daftar_Garam.txt"

KaKbEntry kakb_db[MAX_DB_PH];
int n_dbph = 0;

int run_program() {
    Element periodic_table[118];
    int element_count = 0;

    TreeNode* periodic_tree = NULL;
    Salt* salt_list = NULL;
    Stack operation_history;
    Queue process_queue;

    init_stack(&operation_history);
    init_queue(&process_queue);

    init_periodic_table_from_file(periodic_table, &element_count, ELEMENT_FILE);
    build_periodic_tree(&periodic_tree, periodic_table, element_count);
    read_salts_from_file(&salt_list, SALT_FILE);
    load_kakb_database("ph.txt", kakb_db, &n_dbph);

    int running = 1;
    while (running) {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Tampilkan Tabel Periodik\n");
        printf("2. Tampilkan Tabel Periodik (BST)\n");
        printf("3. Cari Elemen (No Atom)\n");
        printf("4. Cari Elemen (Simbol)\n");
        printf("5. Konfigurasi Elektron\n");
        printf("6. Daftar Garam & Hidrolisis (unstable)\n");
        printf("7. History Operasi\n");
        printf("8. Queue Proses\n");
        printf("9. Hitung Massa Atom Relatif\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");

        int pilihan = 0;
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n"); while(getchar() != '\n');
            continue;
        }
        getchar(); // buang newline

        switch (pilihan) {
        case 1:
            for (int i = 0; i < element_count; i++)
                print_element(&periodic_table[i]);
            push_operation(&operation_history, "Tampilkan Tabel Periodik");
            enqueue_process(&process_queue, "Tampil Tabel Periodik");
            break;

        case 2:
            print_tree_table(periodic_tree);
            push_operation(&operation_history, "Tampilkan Tabel Periodik BST");
            enqueue_process(&process_queue, "Tampil Tabel BST");
            break;

        case 3: {
            int no = 0;
            printf("Masukkan nomor atom: ");
            if (scanf("%d", &no) != 1) { printf("Input tidak valid!\n"); while(getchar() != '\n'); break; }
            getchar();
            Element* el = search_element(periodic_tree, no);
            if (el) print_element(el);
            else printf("Elemen tidak ditemukan!\n");
            push_operation(&operation_history, "Cari Elemen (No Atom)");
            enqueue_process(&process_queue, "Cari Elemen (No Atom)");
            break;
        }

        case 4: {
            char symbol[10];
            printf("Masukkan simbol: ");
            fgets(symbol, sizeof(symbol), stdin);
            symbol[strcspn(symbol, "\n")] = '\0';
            Element* el = search_by_symbol(periodic_table, element_count, symbol);
            if (el) print_element(el);
            else printf("Elemen tidak ditemukan!\n");
            push_operation(&operation_history, "Cari Elemen (Simbol)");
            enqueue_process(&process_queue, "Cari Elemen (Simbol)");
            break;
        }

        case 5: {
            int no;
            printf("Masukkan nomor atom: ");
            if (scanf("%d", &no) != 1) { printf("Input tidak valid!\n"); while(getchar() != '\n'); break; }
            getchar();
            display_electron_config(no);
            OrbitalNode* root = build_electron_config(no);
            printf("\nVisualisasi Konfigurasi Elektron (Tree):\n");
            print_orbital_tree(root, "", 1);
            free_orbital_tree(root);
            push_operation(&operation_history, "Konfigurasi Elektron");
            enqueue_process(&process_queue, "Konfigurasi Elektron");
            break;
        }

        case 6: {
            print_salts(salt_list);
            push_operation(&operation_history, "Daftar Garam");
            enqueue_process(&process_queue, "Daftar Garam");

            char nama[30];
            printf("\n\nMasukkan nama garam: ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = '\0';

            hidrolisis_process(salt_list, nama, &operation_history, &process_queue, kakb_db, n_dbph);
            break;
        }

        case 7:
            print_history(&operation_history);
            break;

        case 8:
            print_queue(&process_queue);
            break;

        case 9: {
            char compound1[100], compound2[100];
            printf("=== KALKULATOR MASSA MOLAR RELATIF ===\n");
            printf("Masukkan simbol senyawa pertama: ");
            if (!fgets(compound1, sizeof(compound1), stdin)) break;
            compound1[strcspn(compound1, "\n")] = '\0';

            printf("Masukkan simbol senyawa kedua: ");
            if (!fgets(compound2, sizeof(compound2), stdin)) break;
            compound2[strcspn(compound2, "\n")] = '\0';

            printf("\n");
            calculate_total_mass(periodic_table, element_count, compound1, compound2);
            break;
        }

        case 0:
            running = 0;
            break;

        default:
            printf("Pilihan tidak valid!\n");
            break;
        }
    }

    // Cleanup
    free_stack(&operation_history);
    free_queue(&process_queue);
    free_tree(periodic_tree);
    free_salt_list(salt_list);

    printf("Terima kasih!\n");
    return 0;
}
