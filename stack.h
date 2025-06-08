#ifndef STACK_H
#define STACK_H

typedef struct StackNode{
    char operation[100];
    struct StackNode *next;
} StackNode;

typedef struct{
    StackNode *top;
} Stack;

//modul
void init_stack(Stack *s); //inisialisasi stak
void push_operation(Stack *s, const char *operation); //add operasi ke stakc
char *pop_operation(Stack *s); //pop oprasi dari stack
int is_stack_empty(Stack *s); //cek apakah stack kosong
void print_history(Stack *s); //print riwayat operasi
void free_stack(Stack *s); //free stack

#endif