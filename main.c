#include "./HashTable.h"
#include <stdio.h>

int main(void) {
    int max_size = 100;

    struct HashTable newHashTable = createHashTable(max_size);
    insertIntoHashTable("cool", 100, &newHashTable);
    insertIntoHashTable("bannas", 200, &newHashTable);
    insertIntoHashTable("apples", 300, &newHashTable);
    
    insertIntoHashTable("apples", 300, &newHashTable);
    insertIntoHashTable("apples", 300, &newHashTable);
    insertIntoHashTable("apples", 300, &newHashTable);
    insertIntoHashTable("apples", 3282347328, &newHashTable);
    insertIntoHashTable("apple", 300, &newHashTable);
    insertIntoHashTable("apples", 600, &newHashTable);
    insertIntoHashTable("this hopefully works?", 400, &newHashTable);

    hashTableToString(newHashTable);

    
    return 0;
}