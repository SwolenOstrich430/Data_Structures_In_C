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

    if(hashTable->entries[hashBucket] == NULL) {
        hashTable->entries[hashBucket] = newEntry;
        return;
    }

    struct Entry *currEntry = hashTable->entries[hashBucket]->next;
    struct Entry *previousEntry = hashTable->entries[hashBucket];

    while(previousEntry->next != NULL) {
        if(strcmp(currEntry->key, key) == 0) {
            currEntry->value = newEntry->value;
            return;
        }

        currEntry = currEntry->next;
        previousEntry = previousEntry->next;
    }

    previousEntry->next = newEntry;
}

void removeEntryFromHashTable(char *key, struct HashTable *hashTable) {
    int hashBucket = getHash(key, hashTable->size);

    struct Entry *entry = hashTable->entries[hashBucket];
    if(entry == NULL) return;


    if(entry->next == NULL && strcmp(entry->key, key) == 0) {
        hashTable->entries[hashBucket] = NULL;
        free(entry->key);
        free(entry); 
        return;
    }

    struct Entry *nextEntry = entry->next;

    while(entry->next != NULL) {
        if(strcmp(nextEntry->key, key) == 0) {
            entry->next = nextEntry->next;
            free(nextEntry->key);
            free(nextEntry); 
            return;
        }

        entry = entry->next;
        nextEntry = nextEntry->next;
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
