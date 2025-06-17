#include "element.h"

void init_periodic_table_from_file(Element *table, int *count, const char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("error: tidak dapat membuka file %s\n", filename);
        *count = 0;
        return
    }
    char line[256];
    *count = 0;
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = '\0';
        Element elem;
        char *token = strtok(line, "|");
        if(!token) continue;
        elem.atomic_number = atoi(token);

        token = strtok(NULL, "|");
        if(!token) continue;
        strncpy(elem.symbol, token, sizeof(elem.symbol) - 1);

        token = strtok(NULL, "|");
        if(!token) continue;
        strncpy(elem.name, token, sizeof(elem.symbol) - 1);

        token = strtok(NULL, "|");
        if(!token) continue;
        elem.atomic_weight = atof(token);
        
        token = strtok(NULL, "|");
        if (!token) continue;
        elem.period = atoi(token);

        token = strtok(NULL, "|");
        if (!token) continue;
        elem.group = atoi(token);

        token = strtok(NULL, "|");
        if (token) strncpy(elem.electron_config, token, sizeof(elem.electron_config) - 1); 
            else elem.electron_config[0] = '\0';

        token = strtok(NULL, "|");
        if (token) strncpy(elem.category, token, sizeof(elem.category) - 1); 
            else elem.category[0] = '\0';

        token = strtok(NULL, "|");
        if (token) elem.electronegativity = atof(token); 
            else elem.electronegativity = 0.0f;

        token = strtok(NULL, "|");
        if (token) strncpy(elem.oxidation_states, token, sizeof(elem.oxidation_states) - 1); 
            else elem.oxidation_states[0] = '\0';

        table[(*count)++] = elem;
        if (*count >= 118) break;
    }
    fclose(file);
}

void search_by_symbol(Element *table, int count, const char *symbol){
    for(int i = 0; i < count; i++){
        if(strcmp(table[i].symbol, symbol) == 0){  
            return &table[i];
        }
    }
    return NULL;
}

void print_element(const Element *elem){
    if(!elem){
        printf("error: elemen tidak ditemukan\n");
        return;
    }
    printf("atomic number: %d\nsymbol: %s\nname: %s\nweight: %.2f\n", 
        elem->atomic_number, elem->symbol, elem->name, elem->atomic_weight);
    printf("period: %d, group: %d\n", 
        elem->period, elem->group);
    printf("electron configuration: %s\ncategory: %s\nelektronegativity:%.2f\noxidation states: %s\n\n",
        elem->electron_config, elem->category, elem->electronegativity, elem->oxidation_states);
}

int parse_compound(const char* formula, Component* components) {
    int comp_count = 0;
    int i = 0;
    int len = strlen(formula);
    
    while (i < len) {
        // Skip whitespace
        while (i < len && isspace(formula[i])) i++;
        if (i >= len) break;
        
        // Baca simbol element (huruf kapital diikuti huruf kecil opsional)
        char symbol[4] = {0};
        int sym_idx = 0;
        
        if (isupper(formula[i])) {
            symbol[sym_idx++] = formula[i++];
            if (i < len && islower(formula[i])) {
                symbol[sym_idx++] = formula[i++];
            }
            if (i < len && islower(formula[i])) {
                symbol[sym_idx++] = formula[i++];
            }
        } else {
            printf("Error: Invalid formula format at position %d\n", i);
            return -1;
        }
        
        // Baca angka (jumlah atom)
        int count = 0;
        if (i < len && isdigit(formula[i])) {
            while (i < len && isdigit(formula[i])) {
                count = count * 10 + (formula[i] - '0');
                i++;
            }
        } else {
            count = 1; // Default 1 jika tidak ada angka
        }
        
        // Cek apakah symbol sudah ada dalam komponen
        int found = 0;
        for (int j = 0; j < comp_count; j++) {
            if (strcmp(components[j].symbol, symbol) == 0) {
                components[j].count += count;
                found = 1;
                break;
            }
        }
        
        // Jika belum ada, tambahkan komponen baru
        if (!found) {
            strcpy(components[comp_count].symbol, symbol);
            components[comp_count].count = count;
            comp_count++;
        }
    }
    
    return comp_count;
}

// Fungsi untuk menghitung massa molar
float calculate_molar_mass(Element* table, int table_count, const char* formula) {
    Component components[50];
    int comp_count = parse_compound(formula, components);
    
    if (comp_count == -1) {
        return -1.0f; // Error dalam parsing
    }
    
    float total_mass = 0.0f;
    
    printf("\nKomponen senyawa %s:\n", formula);
    printf("%-8s %-15s %-10s %-15s %-15s\n", "Symbol", "Nama", "Jumlah", "Massa Atom", "Massa Total");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < comp_count; i++) {
        Element* elem = search_by_symbol(table, table_count, components[i].symbol);
        if (!elem) {
            printf("Error: Element '%s' tidak ditemukan dalam tabel periodik!\n", components[i].symbol);
            return -1.0f;
        }
        
        float component_mass = elem->atomic_weight * components[i].count;
        total_mass += component_mass;
        
        printf("%-8s %-15s %-10d %-15.3f %-15.3f\n", 
               elem->symbol, elem->name, components[i].count, 
               elem->atomic_weight, component_mass);
    }
    
    printf("----------------------------------------------------------------\n");
    printf("Total massa molar: %.3f g/mol\n", total_mass);
    
    return total_mass;
}

// Fungsi untuk menghitung massa total dari dua senyawa
void calculate_total_mass(Element* table, int table_count, const char* compound1, const char* compound2) {
    printf("=== PERHITUNGAN MASSA MOLAR RELATIF ===\n\n");
    
    printf("Senyawa 1: %s\n", compound1);
    float mass1 = calculate_molar_mass(table, table_count, compound1);
    
    if (mass1 < 0) return;
    
    printf("\n==================================================\n\n");
    
    printf("Senyawa 2: %s\n", compound2);
    float mass2 = calculate_molar_mass(table, table_count, compound2);
    
    if (mass2 < 0) return;
    
    printf("\n==================================================\n");
    printf("RINGKASAN:\n");
    printf("Massa molar %s: %.3f g/mol\n", compound1, mass1);
    printf("Massa molar %s: %.3f g/mol\n", compound2, mass2);
    printf("Total massa molar: %.3f g/mol\n", mass1 + mass2);
}