#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 200003

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

int hash(int key) {
    if (key < 0) key = -key;
    return key % TABLE_SIZE;
}

bool find(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key)
            return true;
        temp = temp->next;
    }
    return false;
}

void insert(int key) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void removeKey(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;

    while (temp) {
        if (temp->key == key) {
            if (prev)
                prev->next = temp->next;
            else
                hashTable[index] = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {

    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;

    for (int i = 0; i < numsSize; i++) {
        
        if (find(nums[i]))
            return true;

        insert(nums[i]);

        if (i >= k)
            removeKey(nums[i - k]);
    }

    return false;
}
