#include <stdio.h>
#include <stdlib.h>

typedef struct _List {
    void **array;
    size_t size;
    size_t actual_size;

} List;

typedef struct _Iterator {
    List* lista;
    int index;

} Iterator;