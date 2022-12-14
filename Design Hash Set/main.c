#include <assert.h>
#include "stdlib.h"
#include "stdbool.h"

#define MAX_CALLS (100000)
#define EMPTY (-1)

// This HashSet will resolve collisions via linear probing
// https://leetcode.com/problems/design-hashset/description/

typedef struct{
    int *table;
    int len;
    int n;
} MyHashSet;

bool myHashSetContains(MyHashSet* obj, int key);
void myHashSetRemove(MyHashSet* obj, int key);
void myHashSetAdd(MyHashSet* obj, int key);

void increment(int* input, int len){
    if(*input == len - 1){
        *input = 0;
    } else {
        (*input)++;
    }
}


MyHashSet* myHashSetCreate() {
    MyHashSet *obj = malloc(sizeof(*obj));

    if(!obj){
        return NULL;
    }

    obj->len = MAX_CALLS;
    obj->n = 0;
    obj->table = malloc(MAX_CALLS * (sizeof(int)));

    for(int i = 0; i < obj->len; i++){
        obj->table[i] = EMPTY;
    }

    if(!obj->table){
        free(obj);
        obj = NULL;
    }

    return obj;
}

int hash(int key){ // Super basic hash function to begin
    return key % MAX_CALLS;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    if(myHashSetContains(obj, key) || obj->n >= obj->len) {
        return;
    }

    int hashed = hash(key); // Cannot fully cycle back due to previous condition

    while(obj->table[hashed] != EMPTY){
        increment(&hashed, obj->len);
    }

    obj->table[hashed] = key;
    obj->n++;
}

void myHashSetRemove(MyHashSet* obj, int key) {
    if(!myHashSetContains(obj, key) || obj->n <= 0){
        return;
    }

    int hashed = hash(key); // Cannot fully cycle back due to previous condition

    while(obj->table[hashed] != key){
        increment(&hashed, obj->len);
    }

    obj->table[hashed] = EMPTY;
    obj->n--;
}

bool myHashSetContains(MyHashSet* obj, int key) {
    int hashed = hash(key), cursor = hashed;
    bool first_slot = true;

    while(obj->table[cursor] != EMPTY && obj->table[cursor] != key && (hashed != cursor || first_slot)){
        first_slot = false;
        increment(&cursor, obj->len);
    }

    return (obj->table[cursor] == key);
}

void myHashSetFree(MyHashSet* obj) {
    free(obj->table);
    free(obj);
}

int main(void){
    MyHashSet* obj = myHashSetCreate();

    myHashSetAdd(obj, 1);
    myHashSetAdd(obj, 2);
    assert(myHashSetContains(obj, 1));
    assert(!myHashSetContains(obj, 3));
    myHashSetAdd(obj, 2);
    myHashSetRemove(obj, 2);
    assert(!myHashSetContains(obj, 2));

    myHashSetFree(obj);
}
