#include <stdio.h>
#include <stdlib.h> 
#include "./Entry.h"

// struct definitions and createHashTable function taken from 
// stopped watching after 4:36 https://www.youtube.com/watch?v=wg8hZxMRwcw
struct HashTable {
    int size;
    struct Entry **entries;
};

// taken from this friend: http://www.cse.yorku.ca/~oz/hash.html
int getHash(char *str, int maxHashTableSize) {
    int hash = 0;
    char* currChar;

    for(currChar = str; *currChar != '\0'; currChar++) {
        hash = (31 * hash + (*currChar - '0')) & maxHashTableSize;
    }

    return hash % maxHashTableSize;
}

struct HashTable createHashTable(int maxSize) {
    struct HashTable *newHashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    newHashTable->size = maxSize;
    newHashTable->entries = (struct Entry**)malloc(sizeof(struct Entry*) * maxSize);

    for(int i = 0; i < maxSize; i++) {
        newHashTable->entries[i] = NULL;
    }

    return *newHashTable;
}

void insertIntoHashTable(char *key, unsigned long val, struct HashTable *hashTable) {
    int hashBucket = getHash(key, hashTable->size);

    struct Entry *newEntry = (struct Entry*)malloc(sizeof(struct Entry*));
    newEntry->key = key;
    newEntry->value = val;

    if(hashTable->entries[hashBucket] != NULL) {
        printf("some shit's already there");
    } else {
        hashTable->entries[hashBucket] = newEntry;
    }
}

void hashTableToString(struct HashTable hashTable) {
    printf("START OF HASH TABLE\n");

    for(int i = 0; i < hashTable.size; i++) {
        if(hashTable.entries[i] == NULL) {
            printf("\tindex: %d | pointer: NULL\n", i);
        } else {
            printf("\tindex: %d, pointer: %p key: %s val: %lu\n", i, hashTable.entries[i], 
                hashTable.entries[i]->key, hashTable.entries[i]->value);
        }
    }

    printf("END OF HASH TABLE\n");
}

