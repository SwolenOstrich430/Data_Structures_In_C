#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

struct Node {
    int value;
    struct Node *next;
};

struct Stack {
    struct Node *start;
    void (*pop)(struct Stack *stack);
    void (*push)(int newVal, struct Stack *stack);
    int (*peek)(struct Stack stack);
    int (*getLength)(struct Stack stack);
    void (*forEach)(void (*cb) (int value), struct Stack stack);
};


int getLength(struct Stack stack)  {
    if(stack.start == NULL) {
        return 0;
    }

    int length = 1;
    struct Node *currNode = stack.start;

    while(currNode->next != NULL) {
        length++;
        currNode = currNode->next;
    }

    return length;
}

void pop(struct Stack *stack) {
    if(stack->start == NULL) {
        return;
    }

    struct Node *startNode = stack->start;

    if(startNode->next == NULL) {
        stack->start = NULL;
        free(startNode);

        return;
    } 

    struct Node *secondNode = startNode->next;

    stack->start = secondNode;
    free(startNode);
}

void push(int newVal, struct Stack *stack) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = newVal;
    newNode->next = NULL;

    if(stack->start == NULL) {
        stack->start = newNode;

        return;
    }

    struct Node *currNode = stack->start;

    while(currNode->next != NULL) {
        currNode = currNode->next;
    }

    currNode->next = newNode;
}

int peek(struct Stack stack) {
    if(stack.start == NULL) {
        return NULL;
    }

    struct Node *topNode = stack.start;
    return topNode->value;
}

