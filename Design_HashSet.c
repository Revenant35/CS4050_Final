#include <assert.h>
#include "stdlib.h"
#include "stdbool.h"

#define MAX_CALLS (10000)
#define TOMBSTONE (-2)
#define EMPTY (-1)

// This HashSet will resolve collisions via linear probing
// https://leetcode.com/problems/design-hashset/description/

typedef struct{
    int *table;
    int len;
    int n;
} MyHashSet;

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

bool myHashSetContains(MyHashSet* obj, int key) {
    int hashed = key % MAX_CALLS, i;

    for(i = 0; i < MAX_CALLS && obj->table[(hashed + i) % MAX_CALLS] != EMPTY && obj->table[(hashed + i) % MAX_CALLS] != key; i++);

    return (obj->table[(hashed + i) % MAX_CALLS] == key);
}

void myHashSetAdd(MyHashSet* obj, int key) {
    if(myHashSetContains(obj, key) || obj->n >= obj->len) {
        return;
    }

    int hashed = key % MAX_CALLS, i;

    for(i = 0; i < MAX_CALLS && obj->table[(hashed + i) % MAX_CALLS] != EMPTY; i++);

    obj->table[(hashed + i) % MAX_CALLS] = key;
    obj->n++;
}

void myHashSetRemove(MyHashSet* obj, int key) {
    if(!myHashSetContains(obj, key) || obj->n <= 0){
        return;
    }

    int hashed = key % MAX_CALLS, i;

    for(i = 0; i < MAX_CALLS && obj->table[(hashed + i) % MAX_CALLS] != key; i++);

    obj->table[(hashed + i) % MAX_CALLS] = TOMBSTONE;
    obj->n--;
}

void myHashSetFree(MyHashSet* obj) {
    free(obj->table);
    free(obj);
}

int main(void){
    MyHashSet* obj = myHashSetCreate();

    myHashSetAdd(obj, 1);
    myHashSetAdd(obj, 2);
    myHashSetAdd(obj, 5);
    myHashSetAdd(obj, 4);
    assert(myHashSetContains(obj, 1));
    assert(!myHashSetContains(obj, 3));
    myHashSetAdd(obj, 2);
    myHashSetRemove(obj, 2);
    myHashSetRemove(obj, 5);
    assert(!myHashSetContains(obj, 2));

    myHashSetFree(obj);
}
