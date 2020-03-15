#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

struct Node {
    int value;
    struct Node *next;
};

struct Queue {
    struct Node *start;
    struct Node *end;
    int (*getLength)(struct Queue queue);
    void (*append)(int newVal, struct Queue *queue);
    void (*forEach)(void (*cb) (int value), struct Queue *queue);
    void (*removeStart)(struct Queue *queue);
    int (*peek)(struct Queue *queue);
};

int getLength(struct Queue queue)  {
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

void removeStart(struct Queue *queue) {
    if(queue->start == NULL) {
        return;
    }

    struct Node *startNode = queue->start;

    if(startNode->next == NULL) {
        queue->start = NULL;
        queue->end = NULL;
    } else {
        queue->start = startNode->next;
    }


    free(startNode);
}

void append(int newVal, struct Queue *queue) {
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

void forEach(void (*cb) (int value), struct Queue *queue) {
    if(queue->start == NULL) {
        printf("the list is empty");
        return;
    }

    struct Node *currNode = queue->start;

    while(currNode->next != NULL) {
        (*cb) (currNode->value);
       currNode = currNode->next;
    }

    (*cb) (currNode->value);
}

int peek(struct Queue *queue) {
    if(queue->start == NULL) {
        printf("queue is empty");
        return NULL;
    }

    return queue->start->value;
}