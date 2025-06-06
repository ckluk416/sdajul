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

