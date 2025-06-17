#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "element.h"
#include "bst.h"
#include "salt.h"
#include "stack.h"
#include "queue.h"
#include "electron_config.h"

#define ELEMENT_FILE "tabel_periodik.txt"
#define SALT_FILE "Daftar_Garam.txt"

int main(){
    // Data utama
    Element periodic_table[118];
    int element_count = 0;
    TreeNode* periodic_tree = NULL;
    Salt* salt_list = NULL;
    Stack operation_history;
    Queue process_queue;

    // Inisialisasi struktur data
    init_stack(&operation_history);
    init_queue(&process_queue);

    // Load element dan garam
    init_periodic_table_from_file(periodic_table, &element_count, ELEMENT_FILE);
    build_periodic_tree(&periodic_tree, periodic_table, element_count);
    read_salts_from_file(&salt_list, SALT_FILE);

    int running = 1;
    while (running){
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Tampilkan Tabel Periodik\n");
        printf("2. Tampilkan Tabel Periodik (BST)\n");
        printf("3. Cari Elemen (No Atom)\n");
        printf("4. Cari Elemen (Simbol)\n");
        printf("5. Konfigurasi Elektron\n");
        printf("6. Daftar Garam\n");
        printf("7. Cari Garam\n");
        printf("8. History Operasi\n");
        printf("9. Queue Proses\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");

        int pilihan = 0;
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n"); while(getchar()!='\n');
            continue;
        }
        getchar(); // buang newline

        switch (pilihan ) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 0:
            default:
            
        }


    


    return 0;
}