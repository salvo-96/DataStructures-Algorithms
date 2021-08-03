#include "Header_linked.h"
#include "../Header.h"

size_t get_size_list(List* lista) {
    return lista->size;
}

List* new_empty_list() {
    List* lista = (List*) malloc(sizeof (List));
    if (lista == NULL) {
        fprintf(stderr, "Allocazione di memoria della lista fallita\n");
        exit(EXIT_FAILURE);
    }
    lista->head = (Node*) malloc(sizeof (Node));
    if (lista->head == NULL) {
        fprintf(stderr, "Allocazione di memoria per la head fallita\n");
        exit(EXIT_FAILURE);
    }
    lista->tail = (Node*) malloc(sizeof (Node));
    if (lista->tail == NULL) {
        fprintf(stderr, "Allocazione di memoria per la tail fallita\n");
        exit(EXIT_FAILURE);
    }
    lista->size = 0;
    return lista;
}

Iterator* new_iterator(List* lista) {
    if (lista == NULL) {
        fprintf(stderr, "La lista non e' allocata\n");
        exit(EXIT_FAILURE);
    }
    Iterator* it = (Iterator*) malloc(sizeof (Iterator));
    if (it == NULL) {
        fprintf(stderr, "Allocazione di memoria dell'iteratore fallita\n");
        exit(EXIT_FAILURE);
    }
    it->list = lista;
    it->current = lista->head;
    return it;
}

void destroy_list(List* lista) {
    free(lista);
}

void destroy_iterator(Iterator* it) {
    free(it);
}

size_t list_is_empty(List* lista) {
    if (lista == NULL) {
        fprintf(stderr, "La lista non e' allocata\n");
        exit(EXIT_FAILURE);
    }
    if (get_size_list(lista) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void insert_bottom_list(List* lista, void* val) {
    if (lista == NULL) {
        fprintf(stderr, "La lista non e' allocata\n");
        exit(EXIT_FAILURE);
    }
    if (list_is_empty(lista) == 1) {
        lista->head->elem = val;
        lista->head->prev = lista->head;
        lista->head->next = lista->tail;
        lista->tail->prev = lista->head;
        lista->tail->next = lista->tail;
        lista->size++;
    } else {
        lista->tail->elem = val;
        Node *nodo = (Node*) malloc(sizeof (Node));
        nodo->prev = lista->tail;
        nodo->next = nodo;
        lista->tail->next = nodo;
        lista->tail = nodo;
        lista->size++;
    }
}

void delete_bottom_list(List* lista) {
    if (lista == NULL) {
        fprintf(stderr, "La lista non e' allocata\n");
        exit(EXIT_FAILURE);
    }
    if (list_is_empty(lista) == 1) {
        printf("La lista e' vuota \n");
    } else {
        if (get_size_list(lista) == 1) {
            free(lista->head);
            free(lista->tail);
            lista->head = (Node*) malloc(sizeof (Node));
            lista->tail = (Node*) malloc(sizeof (Node));
            lista->size = 0;
        } else {
            Node* nodo = (Node*) malloc(sizeof (Node));
            nodo = lista->tail->prev;
            nodo = nodo->prev;
            free(nodo->next);
            nodo->next = lista->tail;
            lista->tail->prev = nodo;
            lista->size--;
        }
    }
}

void* get_index_list(List* lista, int index) {
    if (list_is_empty(lista) == 1) {
        printf("La lista e' vuota: \n");
    } else {
        if ((index > get_size_list(lista)) || (index == 0)) {
            printf("Indice non valido: sfora la dimensione della lista\n");
        } else {
            if ((get_size_list(lista) == 1) && (index == 1)) {
                return lista->head->elem;
            }
            if (index == lista->size) {
                Node* temp = (Node*) malloc(sizeof (Node));
                temp = lista->tail->prev;
                return temp->elem;
            } else {
                Node* temp = (Node*) malloc(sizeof (Node));
                temp = lista->head;
                for (int i = 1; i < index; i++) {
                    temp = temp->next;
                }
                return temp->elem;
            }
        }
    }
}

void insert_index_list(List* lista, int index, void* val) {
    if (list_is_empty(lista) == 1 && index == 1) {
        insert_bottom_list(lista, val);
    } else {
        if ((index == 0) || (index > get_size_list(lista))) {
            printf("Gli elementi della lista vanno dall'indice 1 all'indice SIZE \n");
        } else {
            if (index == 1) {
                Node *nodo = (Node*) malloc(sizeof (Node));
                nodo->elem = val;
                nodo->prev = nodo;
                nodo->next = lista->head;
                lista->head->prev = nodo;
                lista->head = nodo;
                lista->size++;
            } else {
                if (index == get_size_list(lista)) {
                    Node* nodo = (Node*) malloc(sizeof (Node));
                    nodo = lista->tail->prev;
                    lista->tail->elem = nodo->elem;
                    nodo->elem = val;
                    Node* new_tail = (Node*) malloc(sizeof (Node));
                    new_tail->next = new_tail;
                    new_tail->prev = lista->tail;
                    lista->tail->next = new_tail;
                    lista->tail = new_tail;
                    lista->size++;
                } else {
                    Node* temp = (Node *) malloc(sizeof (Node));
                    temp = lista->head;
                    for (int i = 1; i < index - 1; i++) {
                        temp = temp->next;
                    }
                    Node* old_node = (Node *) malloc(sizeof (Node));
                    old_node = temp->next;
                    Node* new_node = (Node*) malloc(sizeof (Node));
                    new_node->elem = val;
                    new_node->prev = temp;
                    new_node->next = old_node;
                    old_node->prev = new_node;
                    temp->next = new_node;
                    lista->size++;
                }
            }
        }
    }
}

void delete_index_list(List* lista, int index) {
    if (list_is_empty(lista) == 1) {
        printf("La lista e' vuota\n");
    } else {
        if (index == 0) {
            printf("Indice non valido\n");
        } else {
            if (index == lista->size) {
                delete_bottom_list(lista);
            } else {
                if (index == 1) {
                    lista->head = lista->head->next;
                    free(lista->head->prev);
                    lista->head->prev = lista->head;
                    lista->size--;
                } else {
                    Node* temp = (Node*) malloc(sizeof (Node));
                    temp = lista->head;
                    for (int i = 1; i < index - 1; i++) {
                        temp = temp->next;
                    }
                    Node* temp2 = (Node*) malloc(sizeof (Node));
                    temp2 = temp->next;
                    Node* temp3 = (Node*) malloc(sizeof (Node));
                    temp3 = temp2->next;
                    temp->next = temp3;
                    free(temp2);
                    temp3->prev = temp;
                    lista->size--;
                }
            }
        }
    }
}

/*
int main() {
    List* lista = new_empty_list();
    int i;
    for (i = 1; i <= 10; i++) {
        insert_bottom_list(lista, &i);
    }
    int* p;
    printf("----------STAMPA DOPO INSERIMENTO insert_bottom_list----------\n");
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    delete_bottom_list(lista);
    printf("----------STAMPA DOPO 5 ELIMINAZIONI delete_bottom_list----------\n");
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    int n = 666;
    insert_index_list(lista, get_size_list(lista), &n);
    printf("----------STAMPA DOPO INSERIMENTO DI 666 IN POSIZIONE get_size_list() insert_index_list----------\n");
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO INSERIMENTO DI 777 IN POSIZIONE 1 insert_index_list----------\n");
    int m = 777;
    insert_index_list(lista, 1, &m);
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO INSERIMENTO DI 555 IN POSIZIONE 3 insert_index_list----------\n");
    int o = 555;
    insert_index_list(lista, 3, &o);
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO ELIMINAZIONE IN POSIZIONE 1 delete_index_list----------\n");
    delete_index_list(lista, 1);
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO ELIMINAZIONE IN POSIZIONE get_size_list() delete_index_list----------\n");
    delete_index_list(lista, get_size_list(lista));
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
    printf("----------STAMPA DOPO ELIMINAZIONE IN POSIZIONE 4 delete_index_list----------\n");
    delete_index_list(lista, 4);
    for (i = 1; i <= get_size_list(lista); i++) {
        p = get_index_list(lista, i);
        printf("%d \n", *((int*) p));
    }
}
*/
