#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    void* elem;
    void* next;
    void* prev;


} Node;

typedef struct _List {
    Node* head;
    Node* tail;
    size_t size;

} List;

typedef struct Iterator {
    List *list;
    Node *current;

} Iterator;



