#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void init_stack(Stack *s){
    s->top = NULL;
}

void push_operation(Stack *s, const char *operation){
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
    strcpy(new_node->operation, operation);
    new_node->next = s->top;
    s->top = new_node;
}

char *pop_operation(Stack *s){
    if(s->top == NULL) return NULL;

    StackNode *temp = s->top;
    char *operation = strdup(temp->operation);
    s->top = s->top->next;
    free(temp);
    return operation;
}

int is_stack_empty(Stack *s){
    return s->top == NULL;
}

void print_history(Stack *s){
    printf("\n=== OPERATION HISTORY ===\n");
    StackNode *current = s->top;
    int count = 1;

    if(current == NULL){
        printf("tidak ada operasi yang tercatat.\n");
        return;
    }

    while(current != NULL){
        printf("%d. %s\n", count, current->operation);
        current = current->next;
        count++;
    }
}

void free_stack(Stack *s){
    while(!is_stack_empty(s)){
        char *operation = pop_operation(s);
        free(operation);
    }
}
