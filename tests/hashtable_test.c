#include "../acutest/acutest.h"
#include "hashtable.h"
#include <string.h>


void test_create_hashtable(void) {
    hashtable *ht = create_hashtable(0);
    TEST_CHECK(ht == NULL);

    ht = create_hashtable(5); // should round up to 8
    int size = get_size(ht);
    TEST_CHECK(ht != NULL);
    TEST_CHECK(size == 8);
    free_hashtable(ht);
}

void test_insert_and_search(void) {
    hashtable *ht = create_hashtable(4);

    insert_hash("one", 1, ht);
    insert_hash("two", 2, ht);
    insert_hash("three", 3, ht);

    hashnode *n1 = search_hash("one", ht);
    hashnode *n2 = search_hash("two", ht);
    hashnode *n3 = search_hash("three", ht);
    hashnode *n4 = search_hash("four", ht); // should not exist

    int value = get_value("one", ht);
    int value2 = get_value("two", ht);
    int value3 = get_value("three", ht);
    TEST_CHECK(n1 && value == 1);
    TEST_CHECK(n2 && value2 == 2);
    TEST_CHECK(n3 && value3 == 3);
    TEST_CHECK(n4 == NULL);

    free_hashtable(ht);
}

void test_update_value(void) {
    hashtable *ht = create_hashtable(4);
    insert_hash("hello", 10, ht);
    insert_hash("hello", 99, ht); // update value

    int value = get_value("hello", ht);
    hashnode *n = search_hash("hello", ht);
    TEST_CHECK(n && value == 99);

    free_hashtable(ht);
}

void test_delete(void) {
    hashtable *ht = create_hashtable(4);

    insert_hash("foo", 100, ht);
    insert_hash("bar", 200, ht);

    TEST_CHECK(delete_hash("foo", ht) == true);
    TEST_CHECK(search_hash("foo", ht) == NULL);

    TEST_CHECK(delete_hash("bar", ht) == true);
    TEST_CHECK(search_hash("bar", ht) == NULL);

    TEST_CHECK(delete_hash("baz", ht) == false); // doesn't exist

    free_hashtable(ht);
}

void test_chaining_and_collisions(void) {
    hashtable *ht = create_hashtable(2); // force collisions

    insert_hash("a", 1, ht);
    insert_hash("b", 2, ht); // likely same bucket
    insert_hash("c", 3, ht);

    TEST_CHECK(search_hash("a", ht) != NULL);
    TEST_CHECK(search_hash("b", ht) != NULL);
    TEST_CHECK(search_hash("c", ht) != NULL);

    free_hashtable(ht);
}

void test_resize_and_rehashing(void) {
    hashtable *ht = create_hashtable(2);

    for (int i = 0; i < 20; i++) {
        char key[16];
        sprintf(key, "key%d", i);
        insert_hash(key, i * 10, ht);
    }

    for (int i = 0; i < 20; i++) {
        char key[16];
        sprintf(key, "key%d", i);
        hashnode *n = search_hash(key, ht);
        int val = get_value(key, ht);
        TEST_CHECK(n && val == i * 10);
    }
    int size = get_size(ht);
    TEST_CHECK(size >= 32); // resized at least once
    free_hashtable(ht);
}

void test_next_power_of_two(void) {
    TEST_CHECK(next_power_of_two(0) == 1);
    TEST_CHECK(next_power_of_two(1) == 1);
    TEST_CHECK(next_power_of_two(2) == 2);
    TEST_CHECK(next_power_of_two(3) == 4);
    TEST_CHECK(next_power_of_two(5) == 8);
    TEST_CHECK(next_power_of_two(129) == 256);
}

void test_load_factor_calc(void) {
    hashtable *ht = create_hashtable(8);

    insert_hash("a", 1, ht);
    insert_hash("b", 2, ht);
    insert_hash("c", 3, ht);
    insert_hash("d", 4, ht);

    double factor = load_factor(ht);
    TEST_CHECK(factor == 0.5);

    free_hashtable(ht);
}

TEST_LIST = {
    { "create_hashtable", test_create_hashtable },
    { "insert_and_search", test_insert_and_search },
    { "update_value", test_update_value },
    { "delete", test_delete },
    { "chaining_collisions", test_chaining_and_collisions },
    { "resize_rehash", test_resize_and_rehashing },
    { "next_power_of_two", test_next_power_of_two },
    { "load_factor", test_load_factor_calc },
    { NULL, NULL }
};
