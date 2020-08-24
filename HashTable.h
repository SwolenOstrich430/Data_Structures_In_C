#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
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
    newHashTable->entries = malloc(sizeof(struct Entry*) * maxSize);

    for(int i = 0; i < maxSize; i++) {
        newHashTable->entries[i] = NULL;
    }

    return *newHashTable;
}

void insertIntoHashTable(char *key, unsigned long val, struct HashTable *hashTable) {
    int hashBucket = getHash(key, hashTable->size);

    struct Entry *newEntry = malloc(sizeof(struct Entry));
    newEntry->key = malloc(strlen(key) + 1);
    strcpy(newEntry->key, key);
    newEntry->value = val;
    newEntry->next = NULL;

    if(hashTable->entries[hashBucket] != NULL) {
        hashTable->entries[hashBucket]->next = newEntry;
    } else {
        hashTable->entries[hashBucket] = newEntry;
    }
}

void hashTableToString(struct HashTable hashTable) {
    struct Entry *currEntry;
    
    for(int i = 0; i < hashTable.size; i++) {
        if(hashTable.entries[i] == NULL) {
            printf("\tindex: %d | pointer: NULL\n", i);
            continue;
        }
        
        currEntry = hashTable.entries[i];
        while(currEntry->next != NULL) {
            printf("\tindex: %d, address: %p key: %s val: %d next: %p\n", i, currEntry,
                    currEntry->key, currEntry->value, currEntry->next);
            currEntry = currEntry->next;
        }

        printf("\tindex: %d, pointer: %p key: %s val: %d next: %p\n", i, currEntry,
                currEntry->key, currEntry->value, currEntry->next);
        }

    printf("END OF HASH TABLE\n");
}

