#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <assert.h>
#include "./LinkedList.h"

void addTwo(struct Node* node) {
    node->value = node->value + 1000;
}

int multiplyByTen(int val) {
    return val * 10;
}

bool numEquals(int num1) {
    return num1 != 10060;
}

int main(void) {
    struct Node *node2 = (struct Node*)malloc(sizeof(struct Node));
    node2->value = 2;
    node2->next = NULL;
    struct Node *node1 = (struct Node*)malloc(sizeof(struct Node));
    node1->value = 1;
    node1->next = node2;
    struct Node *node0 = (struct Node*)malloc(sizeof(struct Node));
    node0->value = 0;
    node0->next = node1;
    struct LinkedList linkedList = {node0};
    int length = getLength(linkedList);

    printf("length: %d\n", length);
    assert(length == 3);

    int nodeValToAdd = 3;
    append(nodeValToAdd, &linkedList);

    int lengthAfterAddition = getLength(linkedList);
    printf("length after addition: %d\n", lengthAfterAddition);
    assert(lengthAfterAddition == 4);

    removeAtIndex(2, &linkedList);
    int lengthAfterRemovalAtIndex = getLength(linkedList);
    printf("length after removal: %d\n", lengthAfterRemovalAtIndex);
    assert(lengthAfterRemovalAtIndex == 3);

    append(100, &linkedList);
    int lengthAfterValueToRemoveAddition = getLength(linkedList);
    assert(lengthAfterValueToRemoveAddition == 4);
    removeByValue(100, &linkedList);

    assert(3 == getLength(linkedList));

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct LinkedList *newLinkedList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newLinkedList = createListFromArray(10, arr);
    printf("length of new array: %d\n", getLength(*newLinkedList));
    assert(10 == getLength(*newLinkedList));
    
    forEach(addTwo, *newLinkedList);

    struct Node *n = newLinkedList->start;
    while(n->next != NULL) {
        printf("val: %d\n", n->value);
        n = n->next;
    }

    printf("val: %d\n", n->value);

    struct LinkedList *mapLinkedList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    *mapLinkedList = map(multiplyByTen, *newLinkedList);
    printf("length of new array: %d\n", getLength(*mapLinkedList));
    assert(10 == getLength(*mapLinkedList));
    
    struct Node *n1 = mapLinkedList->start;
    while(n1->next != NULL) {
        printf("val: %d\n", n1->value);
        n1 = n1->next;
    }

    printf("val: %d\n", n1->value);

    struct LinkedList *filterLinkedList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    *filterLinkedList = filter(*numEquals, *mapLinkedList);
    printf("length of new array: %d\n", getLength(*filterLinkedList));
    assert(9 == getLength(*filterLinkedList));
    
    struct Node *n2 = filterLinkedList->start;
    while(n2->next != NULL) {
        printf("val: %d\n", n2->value);
        n2 = n2->next;
    }

    printf("val: %d\n", n2->value);

}