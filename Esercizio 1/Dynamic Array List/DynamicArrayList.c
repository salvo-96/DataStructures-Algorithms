#include "Header_dynamic.h"
#include "../Header.h"

size_t get_size_list(List *lista) {
    if (lista == NULL) {
        fprintf(stderr, "La lista non e' allocata\n");
        exit(EXIT_FAILURE);
    }
    return lista->actual_size;
}

Iterator* new_iterator(List *lista) {
    Iterator *it = (Iterator*) malloc(sizeof (Iterator));
    if (it == NULL) {
        fprintf(stderr, "Alloazione della memoria per l'iteratore fallita\n");
        exit(EXIT_FAILURE);
    }
    it->lista = lista;
    it->index = 0;
    return it;
}

void destroy_iterator(Iterator *it) {
    free(it);
}

void destroy_list(List *lista) {
    free(lista->array);
    free(lista);
}

int list_is_empty(List *lista) {
    if (lista == NULL) {
        fprintf(stderr, "Lista non allocata\n");
        exit(EXIT_FAILURE);
    } else {
        if (get_size_list(lista) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

List* new_empty_list() {
    List *lista = (List*) malloc(sizeof (List));
    if (lista == NULL) {
        fprintf(stderr, "Allocazione della memoria per la lista fallita\n");
        exit(EXIT_FAILURE);
    }
    lista->array = (void **) malloc(2 * sizeof (void*));
    if (lista->array == NULL) {
        fprintf(stderr, "Allocazione della memoria per l'array fallita\n");
        exit(EXIT_FAILURE);
    }
    lista->actual_size = 0;
    lista->size = 2;
    return lista;
}

void insert_bottom_list(List *lista, void* val) {
    if (val == NULL) {
        printf("Valore non valido\n");
    } else {
        if (lista == NULL) {
            printf("Lista non allocata\n");
        } else {
            if (lista->actual_size >= lista->size) {
                lista->array = (void **) realloc(lista->array, 2 * (lista->size) * sizeof (void*));
                if (lista->array == NULL) {
                    fprintf(stderr, "Riallocazione della memoria per l'array fallita\n");
                    exit(EXIT_FAILURE);
                }
                (lista->array)[lista->actual_size] = val;
                (lista->actual_size)++;
                lista->size = 2 * lista->size;
            } else {
                (lista->array)[lista->actual_size] = val;
                (lista->actual_size)++;
            }
        }
    }
}

void delete_bottom_list(List *lista) {
    if (lista == NULL) {
        printf("Lista non allocata\n");
    } else {
        if (lista->actual_size == 1) {
            free(lista->array);
            lista->array = (void **) malloc(2 * sizeof (void*));
            lista->actual_size = 0;
            lista->size = 2;
        } else {
            if (lista->actual_size == 0) {
                printf("La lista e' vuota\n");
            } else {//Ci sono almeno 2 elementi
                (lista->array)[lista->actual_size - 1] = (lista->array)[lista->actual_size];
                lista->actual_size--;
            }
        }
        if (lista->actual_size < lista->size / 2) {
            lista->array = (void **) realloc(lista->array, ((lista->size) * sizeof (void*)) / 2);
            if (lista->array == NULL) {
                fprintf(stderr, "Riallocazione della memoria per l'array fallita\n");
                exit(EXIT_FAILURE);
            }
            lista->size = lista->size / 2;
        }
    }
}

void* get_index_list(List *lista, int index) {
    if (lista == NULL) {
        fprintf(stderr, "Lista non allocata\n");
        exit(EXIT_FAILURE);
    }
    if (index >= lista->actual_size || index < 0) {
        fprintf(stderr, "Indice non valido\n");
        exit(EXIT_FAILURE);
    }
    return (lista->array)[index];
}

void insert_index_list(List *lista, int index, void* val) {
    if (val == NULL || lista == NULL) {
        printf("Valore/Lista non allocato\n");
    } else {
        if (index > lista->actual_size) {
            printf("Indice superiore al numero di elementi attuale\n");
        } else {
            for (int i = lista->actual_size; i > index; i--) {
                (lista->array)[i] = (lista->array)[i - 1];
            }
            (lista->array)[index] = val;
            lista->actual_size++;
        }
        if (lista->actual_size >= lista->size) {
            lista->array = (void **) realloc(lista->array, 2 * (lista->size) * sizeof (void*));
            if (lista->array == NULL) {
                fprintf(stderr, "Riallocazione della memoria per l'array fallita\n");
                exit(EXIT_FAILURE);
            }
            lista->size = 2 * lista->size;
        }

    }
}

void delete_index_list(List* lista, int index) {
    if (lista == NULL) {
        fprintf(stderr, "Lista non allocata \n");
        exit(EXIT_FAILURE);
    }
    if (index >= lista->actual_size) {
        fprintf(stderr, "Indice non valido\n");
        exit(EXIT_FAILURE);
    }
    if ((index == 0) && (get_size_list(lista) == 1)) {
        free(lista->array);
        lista->array = (void **) malloc(2 * sizeof (void*));
        lista->actual_size = 0;
        lista->size = 2;
    } else {
        for (int i = index; i < lista->actual_size; i++) {
            (lista->array)[i] = (lista->array)[i + 1];
        }
        lista->actual_size--;
    }
    if (lista->actual_size < lista->size / 2) { //controllo dim
        lista->array = (void **) realloc(lista->array, ((lista->size) * sizeof (void*)) / 2);
        if (lista->array == NULL) {
            fprintf(stderr, "realloc failure");
            exit(EXIT_FAILURE);
        }
        lista->size = lista->size / 2;
    }
}

/*
int main() {
    List* lista = new_empty_list();
    int i;
    int* p;
    for (i = 0; i < 10; i++) {
        insert_bottom_list(lista, &i);
    }
    printf("----------STAMPA DOPO INSERIMENTO DI 10 ELEMENTI----------\n");
    for (i = 0; i < get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    printf("----------STAMPA DOPO CANCELLAMENTO DI DEGLI ULTIMI 5 ELEMENTI delete_bottom_list----------\n");
    for (i = 0; i < get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO INSERIMENTO DI numero 666 777 999 in posizione 0 6 get_size_list() insert_index_list----------\n");
    int q, w, e;
    q = 666;
    w = 777;
    e = 999;
    insert_index_list(lista, 0, &q);
    insert_index_list(lista, 6, &w);
    insert_index_list(lista, get_size_list(lista), &e);
    for (i = 0; i < get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO ELIMINAZIONE DI posizione 3 5 get_size_list() insert_index_list----------\n");
    delete_index_list(lista, 3);
    delete_index_list(lista, 5);
    for (i = 0; i < get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
}
*/
