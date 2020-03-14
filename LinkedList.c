#include <stdio.h>
#include <stdlib.h> 

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
    void (*append)(int value, struct LinkedList *ll);
    void (*forEach)(void (*cb) (), struct LinkedList ll);
    struct LinkedList (*map)(int (*cb) (int val), struct LinkedList list);
};
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

// just testing for now, will export this module to be used in 
// separate file once it's implemented
int main(void) {
    struct Node firstNode = { 1, 0 };
    struct LinkedList firstLinkedList = { NULL, &append, &forEach, &map };
    firstLinkedList.append(1, &firstLinkedList);
    firstLinkedList.append(2, &firstLinkedList);
    firstLinkedList.append(3, &firstLinkedList);

    firstLinkedList.forEach(&printElem, firstLinkedList);
    struct LinkedList newLinkedList = firstLinkedList.map(&addOneVal, firstLinkedList);
    

    newLinkedList.forEach(&printElem, newLinkedList);
    // struct Node *n = newLinkedList.start;
    // printf("pointer to node: %p", n);
    // printf("value at node: %d", n->value);
    // printf("pointer to next node: %p", n->next);

    return 0;
}