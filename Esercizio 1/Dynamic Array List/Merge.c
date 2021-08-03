#include "DynamicArrayList.c"

void* minore(void* a, void* b) {
    if (*((int*) a) < *((int*) b)) {
        return a;
    } else {
        return b;
    }
}

List* merge(void*(*function)(void*, void*), List* lista1, List* lista2) {
    List* ordered_list = new_empty_list();
    size_t size1 = get_size_list(lista1);
    size_t size2 = get_size_list(lista2);
    int i1 = 0;
    int i2 = 0;
    while ((i1 != size1) && (i2 != size2)) {
        insert_bottom_list(ordered_list, function(get_index_list(lista1, i1), get_index_list(lista2, i2)));
        if (function(get_index_list(lista1, i1), get_index_list(lista2, i2)) == get_index_list(lista1, i1)) {
            i1++;
        } else {
            i2++;
        }
    }
    if (i1 == size1) {//Ha terminato gli elemeni della lista 1 e copia quelli rimanenti dalla lista 2
        while (i2 != size2) {
            insert_bottom_list(ordered_list, get_index_list(lista2, i2));
            i2++;
        }
        return ordered_list;
    } else {//Ha terminato gli elemeni della lista 2 e copia quelli rimanenti dalla lista 1
        if (i2 == size2) {
            while (i1 != size1) {
                insert_bottom_list(ordered_list, get_index_list(lista1, i1));
                i1++;
            }
            return ordered_list;
        } else {
            return ordered_list;
        }
    }
}

int main() {
    List* lista1 = new_empty_list();
    List* lista2 = new_empty_list();
    int a, b, c, d;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    insert_bottom_list(lista1, &a);
    insert_bottom_list(lista1, &c);
    insert_bottom_list(lista2, &b);
    insert_bottom_list(lista2, &d);
    void* (*pointer)(void* a, void* b);
    pointer = minore;
    List* ordered = merge(pointer, lista1, lista2);
    int* p;
    for (int i = 0; i < get_size_list(ordered); i++) {
        p = get_index_list(ordered, i);
        printf("%d \n", *((int*) p));
    }
}