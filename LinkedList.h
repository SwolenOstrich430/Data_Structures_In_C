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
// "member method" that adds a new node to the end 
// of the LinkedList
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

// removes an element in the array at the index specified in the 
// input parameter
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

// implementing javascript's forEach array method on LinkedList
// loops through all nodes in the list and calls a callback
// function on each node. 
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

// implementing javascript's map method => for every element in 
// the array, perform an operation on the value of it with the 
// callback function, and add it to a new array
struct LinkedList map(int (*cb) (int val), struct LinkedList list) {
    // starting new list for nodes to be appended to 
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
    // while tracking node from original list does is not the last node in the list
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

