#include "unity.h"
#include "DynamicArrayList.c"

void test_get_size_list() {
    List* lista = new_empty_list();
    TEST_ASSERT_EQUAL_INT(0, get_size_list(lista));
}

void test_list_is_empty() {
    List* lista = new_empty_list();
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(lista));
}

void test_new_empty_list() {
    List* lista = new_empty_list();
    TEST_ASSERT_NOT_NULL(lista);
}

void test_insert_bottom_list() {
    List* lista = new_empty_list();
    int a = 100;
    insert_bottom_list(lista, &a);
    TEST_ASSERT_EQUAL_INT(a, *((int*) (get_index_list(lista, 0))));
}

void test_delete_bottom_list() {
    List* lista = new_empty_list();
    int a = 100;
    insert_bottom_list(lista, &a);
    delete_bottom_list(lista);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(lista));
}

void test_delete_index_list() {
    List* lista = new_empty_list();
    int a = 100;
    insert_bottom_list(lista, &a);
    delete_index_list(lista, 0);
    TEST_ASSERT_EQUAL_INT(1, list_is_empty(lista));
}

void test_insert_index_list() {
    List* lista = new_empty_list();
    int a = 100;
    insert_index_list(lista, 0, &a);
    TEST_ASSERT_EQUAL_INT(a, *((int*) (get_index_list(lista, 0))));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_size_list);
    RUN_TEST(test_list_is_empty);
    RUN_TEST(test_new_empty_list);
    RUN_TEST(test_insert_bottom_list);
    RUN_TEST(test_delete_bottom_list);
    RUN_TEST(test_delete_index_list);
    RUN_TEST(test_insert_index_list);
    return UNITY_END();
}