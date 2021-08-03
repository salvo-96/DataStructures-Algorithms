#include "Header_linked.h"

int validate_iterator(Iterator* it) {
    if (it->current->next == it->current)
        return 0;
    else
        return 1;
}

void* get_elem(Iterator* it) {
    return it->current->elem;
}

void move_next(Iterator* it) {

    if ((validate_iterator(it)) == 1)
        it->current = it->current->next;
    else {
        printf("L'iteratore non e' piu valido");
    }
}

int main() {
}