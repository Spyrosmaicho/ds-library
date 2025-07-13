#include "list.h"
#include "../acutest/acutest.h"
#include <stdlib.h>
/**
 *  All tests have been made in a way to showcase
 *  the effectiveness of every function implemented.
 *  Please review the code for every test to understand
 *  the cases it covers.
*/


void test_create_and_add(void) {
    List *list = create_list();
    TEST_CHECK(list != NULL);
    TEST_CHECK(list_empty(list));

    Node *head = get_head(list);
    TEST_CHECK(head == NULL);
    
    add_node(list, 10);
     add_node(list, 20);
    add_node(list, 30);
    TEST_CHECK(list_size(list) == 3);


    free_list(list);
}

void test_list_empty(void) {
    List *list = create_list();
    TEST_CHECK(list_empty(list) == true);

    add_node(list,42);
    TEST_CHECK(list_empty(list) == false);

    free_list(list);
}

void test_list_size(void) 
{
    List *list = create_list();
    TEST_CHECK(list_size(list) == 0);
    int values[] = {11, 22, 33, 44, 55};
    for(int i = 0;i<5;i++) add_node(list,values[i]);
    TEST_CHECK(list_size(list) == 5);
    free_list(list);
}


void test_search(void) 
{
    List *list = create_list();
    TEST_CHECK(list_empty(list) == true);
    int values[10] = {0};

    for(int i = 0; i < 10; i++) values[i] = i * 10; // Fill with multiples of 10
    
    for(int i = 0; i < 10; i++) add_node(list, values[i]);

    TEST_CHECK(search_list(list, 10) == true);
    TEST_CHECK(search_list(list, 42) == false);

    free_list(list);
}


void test_free_node(void) 
{
    List *list = create_list();
    TEST_CHECK(list_empty(list) == true);
    int values[10] = {0};
    for(int i = 0; i < 10; i++) values[i] = i * i;
    
    for(int i = 0; i < 10; i++) add_node(list, values[i]);

    free_node(list, 4);
    TEST_CHECK(list_size(list) == 9);
    free_node(list,0);
    TEST_CHECK(list_size(list) == 8);
    free_node(list,4);
    TEST_CHECK(list_size(list) == 8); // Should not change size since 4 was already removed
    free_node(list, 100); // Trying to remove a non-existing value
    TEST_CHECK(list_size(list) == 8); // Size should remain the same

    free_list(list);
}

void test_free_list(void) {
    int values[100] = {0};
    List *list = create_list();
    TEST_CHECK(list != NULL);

    for(int i = 0; i < 100; i++) values[i] = i * 2; // Fill with even numbers
    for(int i = 0; i < 100; i++) add_node(list, values[i]);

    free_list(list);

    // After freeing, the list should not be accessible, but we can't check it directly.
    // We can only ensure that the function runs without errors.
    TEST_CHECK(true);
}

TEST_LIST = {
    { "create_and_add", test_create_and_add },
    { "list_empty", test_list_empty },
    { "list_size", test_list_size },
    { "search", test_search },
    { "free_node", test_free_node },
    { "free_list", test_free_list },
    { NULL, NULL } 
};