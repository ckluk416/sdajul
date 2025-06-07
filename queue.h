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
void init_queue(Queue *q); // inisialisasi queue
void enqueue_process(Queue *q, const char *process); //enque proses ke dlm queue
char *dequeue_process(Queue *q); // deque proses dari queue
int is_queue_empty(Queue *q); // cek status queue (apakah kosong)
void print_queue(Queue *q); // print queue
void free_queue(Queue *q); // free queue

#endif
