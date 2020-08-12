#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <assert.h>
#include "./LinkedList.h"

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
    printf("length after removal: %d/n", lengthAfterRemovalAtIndex);
    assert(lengthAfterRemovalAtIndex == 3);

    append(100, &linkedList);
    int lengthAfterValueToRemoveAddition = getLength(linkedList);
    assert(lengthAfterValueToRemoveAddition == 4);
    removeByValue(100, &linkedList);
    
    assert(3 == getLength(linkedList));


}