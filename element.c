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
        if (token) strncpy(elem.electron_config, token, sizeof(elem.electron_config) - 1); else elem.electron_config[0] = '\0';

        token = strtok(NULL, "|");
        if (token) strncpy(elem.category, token, sizeof(elem.category) - 1); else elem.category[0] = '\0';

        token = strtok(NULL, "|");
        if (token) elem.electronegativity = atof(token); else elem.electronegativity = 0.0f;

        token = strtok(NULL, "|");
        if (token) strncpy(elem.oxidation_states, token, sizeof(elem.oxidation_states) - 1); else elem.oxidation_states[0] = '\0';

        table[(*count)++] = elem;
        if (*count >= 118) break;
    }
    fclose(file);
}