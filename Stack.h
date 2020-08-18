#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "./Node.h"

struct Stack {
    struct Node *start;
};


int getStackLength(struct Stack stack)  {
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
    newNode->next = stack->start;

    stack->start = newNode;
}

struct Node* peek(struct Stack stack) {
    if(stack.start == NULL) {
        return NULL;
    }

    struct Node *topNode = stack.start;
    return topNode;
}

struct Stack createStackFromArray(int sizeOfArray, int *arr) {
    struct Stack *newStack = (struct Stack*)malloc(sizeof(struct Stack));
    newStack->start = NULL;

    for(int i = sizeOfArray - 1; i >= 0; i--) {
        push(arr[i], newStack);      
    }

    return *newStack;
}