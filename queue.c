#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void init_queue(Queue *q){
    q->front = q->rear = NULL;
}

void enqueue_process(Queue *q, const char *process){
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    strcpy(new_node->process, process);
    new_node->next = NULL;

    if(q->rear == NULL){
        q->front = q->rear = new_node;
    } else{
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

char *dequeue_process(Queue *q){
    if(q->front == NULL) return NULL;

    QueueNode *temp = q->front;
    char *process = strdup(temp->process);
    q->front = q->front->next;

    if(q->front == NULL){
        q->rear = NULL;
    }

    free(temp);
    return process;
}

int is_queue_empty(Queue *q){
    return q->front == NULL;
}

void print_queue(Queue *q){
    printf("\n=== PROCESS QUEUE ===\n");
    QueueNode *current = q->front;
    int count = 1;

    if(current == NULL){
        printf("tidak ada proses dalam queue.\n");
        return;
    }

    while(current != NULL){
        printf("%d. %s\n", count, current->process);
        current = current->next;
        count++;
    }
}

void free_queue(Queue *q) {
    while (!is_queue_empty(q)) {
        char *process = dequeue_process(q);
        free(process);
    }
}