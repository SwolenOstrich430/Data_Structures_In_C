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
    void (*forEach)(void (*cb) (int value), struct Stack stack);
};


void pop(struct Stack *stack) {

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
    struct Node *topNode = stack.start;

    return topNode->value;
}

void forEach(void (*cb) (int value), struct Stack stack) {
    struct Node *currNode = stack.start;

    while(currNode->next != NULL) {
        (*cb) (currNode->value);
       currNode = currNode->next;
    }

    (*cb) (currNode->value);
}

void printElem(int val) {
    printf("current elem: %d\n", val);
}


int main(void) {
    struct Stack newStack = { NULL, &pop, &push, &peek, &forEach };

    newStack.push(1, &newStack);
    newStack.push(2, &newStack);
    newStack.push(3, &newStack);
    newStack.forEach(&printElem, newStack);

    int topVal = newStack.peek(newStack);
    printf("sadfasdffasfasfasfasfasfadfs\n");
    printf("top value: %d", topVal);
    return 0;
}