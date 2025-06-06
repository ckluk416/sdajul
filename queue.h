#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode{
    char process[50];
    struct QueueNode *next;
} QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
} Queue;

// modul
void init_queue(Queue *q);
void enqueue_process(Queue *q, const char *process);
char *dequeue_process(Queue *q);
int is_queue_empty(Queue *q);
void print_queue(Queue *q);
void free_queue(Queue *q);

#endif
