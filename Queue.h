#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "./Node.h"

struct Queue {
    struct Node *start;
    struct Node *end;
};

bool isEmpty(struct Queue queue) {
    return queue.start == NULL;
}

int getQueueLength(struct Queue queue)  {
    if(queue.start == NULL) {
        return 0;
    }

    int length = 1;
    struct Node *currNode = queue.start;

    while(currNode->next != NULL) {
        length++;
        currNode = currNode->next;
    }

    return length;
}

struct Node* dequeue(struct Queue *queue) {
    if(queue->start == NULL) {
        return NULL;
    }

    struct Node *startNode = queue->start;

    if(startNode->next == NULL) {
        queue->start = NULL;
        queue->end = NULL;
    } else {
        queue->start = startNode->next;
    }

    return startNode;
}

void enqueue(int newVal, struct Queue *queue) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = newVal;
    newNode->next = NULL;

    if(queue->start == NULL) {
        queue->end = newNode;
        queue->start = newNode;
    } else {
        queue->end->next = newNode;
        queue->end = newNode;
    }
}

struct Queue createQueueFromArray(int sizeOfQueue, int *arr) {
    struct Queue *newQueue = (struct Queue*)malloc(sizeof(struct Queue));
    newQueue->start = NULL;
    newQueue->end = NULL;

    for(int i = sizeOfQueue - 1; i >= 0; i--) {
        enqueue(arr[i], newQueue);
    }

    return *newQueue;
}

struct Node* front(struct Queue *queue) {
    if(queue->start == NULL) {
        printf("queue is empty");
        return NULL;
    }

    return queue->start;
}

struct Node* end(struct Queue *queue) {
    if(queue->start == NULL) {
        printf("queue is empty");
        return NULL;
    }

    return queue->end;
}