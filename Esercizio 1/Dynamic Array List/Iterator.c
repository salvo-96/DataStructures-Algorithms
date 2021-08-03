#include "Header_dynamic.h"

void move_next(Iterator* it) {
    it->index++;
}

void* get_elem(Iterator *it) {
    return (it->lista->array)[it->index];
}

int iterator_validate(Iterator* it) {
    if (it->index >= it->lista->actual_size) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
}