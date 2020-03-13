#include <stdio.h>
#include <stdlib.h> 

// struct containing a value and a pointer to the 
// next node in the linked list. If node in list 
// is list.length - 2, pointer is null 
typedef struct Node {
    int value;
    struct Node *next;
} Node;
// struct containing the start to the first node 
// in the list in addition to pseudomember methods 
// (not sure if this is correct in C. If someone 
// who's looking at this -- not that anyone will --
// knows what's good, that'd be gret to hear)
struct LinkedList {
    struct Node *start;
    void (*append)(int value, struct LinkedList ll);
    void (*forEach)(void (*cb) (), struct LinkedList ll);
};
// "member method" that adds a new node to the end 
// of the LinkedList
void append(int newVal, struct LinkedList list) {
    struct Node *currNode = list.start;
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->value = newVal;
    newNode->next = NULL;

    while(currNode->next != NULL) {
        currNode = currNode->next;
    }

    currNode->next = newNode;
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
// dummy function we're using to test the forEach method
void printElem(struct Node *node) {
    printf("value at current elem is: %d\n", node->value);
}

// just testing for now, will export this module to be used in 
// separate file once it's implemented
int main(void) {
    struct Node firstNode = { 1, 0 };
    struct LinkedList firstLinkedList = { &firstNode, &append, &forEach };

    firstLinkedList.append(2, firstLinkedList);
    firstLinkedList.append(3, firstLinkedList);

    firstLinkedList.forEach(&printElem, firstLinkedList);
    return 0;
}