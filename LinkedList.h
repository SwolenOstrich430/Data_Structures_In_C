#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "./Node.h"

struct LinkedList {
    struct Node *start;
};

struct LinkedList* createListFromArray(int sizeOfArray, int *arr) {
    struct LinkedList *newLinkedList = (struct LinkedList*)malloc(sizeof(struct Node));
    if(sizeOfArray <= 0) return newLinkedList;

    struct Node *previousNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node *currNode;

    for(int i = sizeOfArray - 1; i >= 1; i--) {
        currNode = (struct Node*)malloc(sizeof(struct Node));

        if(i == sizeOfArray - 1) {
            previousNode->next = NULL;
            previousNode->value = arr[i];
        }

        currNode->next = previousNode;
        currNode->value = arr[i - 1];
        previousNode = currNode;        
    }

    newLinkedList->start = currNode;

    return newLinkedList;
}

//  get the length of the list 
int getLength(struct LinkedList list) {
    if(list.start == NULL) return 0;

    int length = 1;
    struct Node *currNode = list.start;

    while(currNode->next != NULL) {
        length++;
        currNode = currNode->next;
    }

    return length;
}

void append(int newVal, struct LinkedList *list) {
    struct Node *currNode = list->start;
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->value = newVal;
    newNode->next = NULL;

    if(currNode == NULL) {
        list->start = newNode;
        return;
    } 
    
    while(currNode->next != NULL) {
        currNode = currNode->next;
    }

    currNode->next = newNode;
    
}

void removeAtIndex(int removeIndex, struct LinkedList *list) {
    int listLength = getLength(*list);
    if(listLength == 0 || removeIndex > listLength - 1) return;

    struct Node *currNode = list->start->next;
    struct Node *previousNode = list->start;

    if(removeIndex == 0) {
        list->start = currNode;
        free(previousNode);

        return;
    }

    int counter = 1;

    while(currNode->next != NULL) {
        if(counter == removeIndex) {
            previousNode->next = currNode->next;
        
            free(currNode);
            return;
        }

        counter++;
        previousNode = currNode;
        currNode = currNode->next;
    }

    if(removeIndex == listLength - 1) {
        previousNode->next = NULL;
        free(currNode);
    }
}

void removeByValue(int valueToRemove, struct LinkedList *list) {
    int listLength = getLength(*list);
    if(listLength == 0) return;

    struct Node *currNode = list->start->next;
    struct Node *previousNode = list->start;

    if(previousNode->value == valueToRemove) {
        list->start = currNode;
        free(previousNode);

        return;
    }

    int counter = 1;

    while(currNode->next != NULL) {
        if(currNode->value == valueToRemove) {
            previousNode->next = currNode->next;
        
            free(currNode);
            return;
        }

        counter++;
        previousNode = currNode;
        currNode = currNode->next;
    }

    if(currNode->value == valueToRemove) {
        previousNode->next = NULL;
        free(currNode);
    }
}


void forEach(void (*cb) (struct Node *node), struct LinkedList list) {
    if(list.start == NULL) {
        printf("the list is empty");
        return;
    }

    struct Node *currNode = list.start;

    while(currNode->next != NULL) {
        (*cb) (currNode);
        currNode = currNode->next;
    }

    (*cb) (currNode);
}

struct LinkedList map(int (*cb) (int val), struct LinkedList list) {
    struct LinkedList *newLinkedList = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    newLinkedList->start = NULL;

    if(list.start == NULL) {
        printf("the list is empty");
        return *newLinkedList;
    }

    int newVal;
    struct Node *currNode = list.start;

    while(currNode->next != NULL) {
        newVal = (*cb) (currNode->value);
        append(newVal, newLinkedList);

        currNode = currNode->next;
    }

    int lastNewVal = (*cb) (currNode->value);
    append(lastNewVal, newLinkedList);

    return *newLinkedList;
}

struct LinkedList filter(bool (*cb) (int val), struct LinkedList list) {
    struct LinkedList *newLinkedList = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    newLinkedList->start = NULL;

    if(list.start == NULL) {
        printf("the list is empty");
        return *newLinkedList;
    }

    struct Node *currNode = list.start;
    bool shouldAddToArray;
    
    while(currNode->next != NULL) {
        shouldAddToArray = (*cb) (currNode->value);

        if(shouldAddToArray) {
            append(currNode->value, newLinkedList);
        }

        currNode = currNode->next;
    }

    shouldAddToArray = (*cb) (currNode->value);
    if(shouldAddToArray) append(currNode->value, newLinkedList);

    return *newLinkedList;
    
}

