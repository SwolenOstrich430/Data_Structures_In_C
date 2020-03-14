#include <stdio.h>
#include <stdlib.h> 
#include<stdbool.h>

// struct containing a value and a pointer to the 
// next node in the linked list. If node in list 
// is list.length - 2, pointer is null 
struct Node {
    int value;
    struct Node *next;
};
// struct containing the start to the first node 
// in the list in addition to pseudomember methods 
// (not sure if this is correct in C. If someone 
// who's looking at this -- not that anyone will --
// knows what's good, that'd be gret to hear)
struct LinkedList {
    struct Node *start;
    int (*getLength)(struct LinkedList list);
    void (*append)(int value, struct LinkedList *list);
    void(*removeAtIndex)(int removeIndex, struct LinkedList *list);
    void (*forEach)(void (*cb) (), struct LinkedList list);
    struct LinkedList (*map)(int (*cb) (int val), struct LinkedList list);
    struct LinkedList (*filter)(bool (*cb) (int val), struct LinkedList list);
};
// get the length of the list 
int getLength(struct LinkedList list) {
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
    } else {
        while(currNode->next != NULL) {
            currNode = currNode->next;
        }

        currNode->next = newNode;
    }
}
// removes an element in the array at the index specified in the 
// input parameter

// need to do different things if index is 0 or length - 1

void removeAtIndex(int removeIndex, struct LinkedList *list) {
    struct Node *currNode = list->start->next;
    struct Node *previousNode = list->start;

    if(removeIndex == 0) {
        list->start = currNode;
        free(previousNode);

        return;
    }

    int listLength = list->getLength(*list) - 1;
    int counter = 1;
    printf("target remove is %d\n", removeIndex);

    while(currNode->next != NULL && counter <= removeIndex) {
        printf("getting in loop with index: %d\n", counter);
        if(counter == removeIndex) {
            printf("we got in the if statement\n");
            previousNode->next = currNode->next;

            free(currNode);
        }

        counter++;
        previousNode = currNode;
        currNode = currNode->next;
    }

    printf("length: %d\n", listLength);
    if(removeIndex == listLength) {
        printf("we go in the last if statement\n");
        previousNode->next = NULL;
        free(currNode);
    }
}
// implementing javascript's forEach array method on LinkedList
// loops through all nodes in the list and calls a callback
// function on each node. 
void forEach(void (*cb) (struct Node*), struct LinkedList list) {
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
    // get the starting node of the list to copy
    struct Node *currNod = list.start;
    // starting new list for nodes to be appended to 
    struct LinkedList *newLinkedList = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    // initializing new linked list with member methods and null as pointer to starting node
    newLinkedList->append = &append;
    newLinkedList->forEach = &forEach;
    newLinkedList->map = &map;
    newLinkedList->start = NULL;
    // getting node to track current node in original list
    struct Node *currNode = list.start;
    // while tracking node from original list does is not the last node in the list
    while(currNode->next != NULL) {
        int newVal = (*cb) (currNode->value);
        newLinkedList->append(newVal, newLinkedList);

        currNode = currNode->next;
    }

    int lastNewVal = (*cb) (currNode->value);
    newLinkedList->append(lastNewVal, newLinkedList);

    return *newLinkedList;
}
// implementing javascript's filter method => for every element in 
// the array, if the value of a node returns true when passed into 
// the given callback function, add it to a new array, if it doesn't, 
// do not add it to the new array. 
struct LinkedList filter(bool (*cb) (int val), struct LinkedList list) {
    // get the starting node of the list to copy
    struct Node *currNod = list.start;
    // starting new list for nodes to be appended to 
    struct LinkedList *newLinkedList = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    // initializing new linked list with member methods and null as pointer to starting node
    newLinkedList->append = &append;
    newLinkedList->forEach = &forEach;
    newLinkedList->map = &map;
    newLinkedList->filter = &filter;
    newLinkedList->start = NULL;
    // getting node to track current node in original list
    struct Node *currNode = list.start;
    // while tracking node from original list does is not the last node in the list
    while(currNode->next != NULL) {
        bool shouldAddToArray = (*cb) (currNode->value);

        if(shouldAddToArray) {
            newLinkedList->append(currNode->value, newLinkedList);
        }

        currNode = currNode->next;
    }

    bool shouldAddFinalToArray = (*cb) (currNode->value);
    if(shouldAddFinalToArray) newLinkedList->append(currNode->value, newLinkedList);

    return *newLinkedList;
    
}

void addOne(struct Node *node) {
    node->value = node->value + 1;
}

int addOneVal(int value) {
    int *newVal = (int*)malloc(sizeof(int));
    *newVal = value + 7;

    return *newVal;
}

// dummy function we're using to test the forEach method
void printElem(struct Node *node) {
    printf("value at current elem is: %d\n", node->value);
}

bool isEven(int val) {
    return val % 2 == 0;
}

// just testing for now, will export this module to be used in 
// separate file once it's implemented
int main(void) {
    struct LinkedList firstLinkedList = { NULL, &getLength, &append, &removeAtIndex, &forEach, &map, &filter };
    firstLinkedList.append(1, &firstLinkedList);
    firstLinkedList.append(2, &firstLinkedList);
    firstLinkedList.append(3, &firstLinkedList);
    firstLinkedList.append(4, &firstLinkedList);
    firstLinkedList.append(5, &firstLinkedList);


    firstLinkedList.forEach(&printElem, firstLinkedList);
    
    firstLinkedList.removeAtIndex(4, &firstLinkedList);
    firstLinkedList.forEach(&printElem, firstLinkedList);
    

    // struct Node *n = newLinkedList.start;
    // printf("pointer to node: %p", n);
    // printf("value at node: %d", n->value);
    // printf("pointer to next node: %p", n->next);

    return 0;
}