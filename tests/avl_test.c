#include "../acutest/acutest.h"
#include "avl.h"

void test_insert_and_search(void) 
{
    avl *root = NULL;

    // Insert a series of values
    int values[] = {10, 20, 5, 6, 15, 30, 25, 35};
    for (int i = 0; i < 8; i++)
        root = insert_avl(root, values[i]);

    // Search for all inserted values
    for (int i = 0; i < 8; i++)
        TEST_CHECK(search_avl(root, values[i]) != NULL);

    // Search for a non-existent value
    TEST_CHECK(search_avl(root, 1000) == NULL);

    destroy_avl(root);
}

void test_balancing(void) {
    avl *root = NULL;
    avl *root2 = NULL;
    avl *root3 = NULL;
    avl *root4 = NULL;

    // Insert elements in ascending order (to trigger rotations)
    root = insert_avl(root, 10);
    root = insert_avl(root, 20);
    root = insert_avl(root, 30); // triggers left rotation

    int key = get_key(root);
    int left_key = get_left_key(root);
    int right_key = get_right_key(root);
    TEST_CHECK(key == 20); // Balanced root after rotation
    TEST_CHECK(left_key == 10);
    TEST_CHECK(right_key == 30);
    TEST_CHECK(get_height(root) == 2);
    destroy_avl(root);

    int val = 20;
    for(int i = 0;i<3;i++) 
    {
        root2 = insert_avl(root2,val);
        val -=5;
    }

    int key2 = get_key(root2);
    int left_key2 = get_left_key(root2);
    int right_key2 = get_right_key(root2);
    TEST_CHECK(key2 == 15); // Balanced root after rotation
    TEST_CHECK(left_key2 == 10);
    TEST_CHECK(right_key2 == 20);
    TEST_CHECK(get_height(root2) == 2);
    destroy_avl(root2);

    // LR Rotation Test
    root3 = insert_avl(root3, 30);
    root3 = insert_avl(root3, 10);
    root3 = insert_avl(root3, 20); 

    int key3 = get_key(root3);
    int left_key3 = get_left_key(root3);
    int right_key3 = get_right_key(root3);

    TEST_CHECK(key3 == 20);
    TEST_CHECK(left_key3 == 10);
    TEST_CHECK(right_key3 == 30);
    destroy_avl(root3);


    //RL Rotation test
    root4 = insert_avl(root4, 10);
    root4 = insert_avl(root4, 30);
    root4 = insert_avl(root4, 20); 

    int key4 = get_key(root4);
    int left_key4 = get_left_key(root4);
    int right_key4 = get_right_key(root4);

    TEST_CHECK(key4 == 20);
    TEST_CHECK(left_key4 == 10);
    TEST_CHECK(right_key4 == 30);
    destroy_avl(root4);

}

void test_deletion_leaf(void) {
    avl *root = NULL;
    root = insert_avl(root, 50);
    root = insert_avl(root, 30);
    root = insert_avl(root, 70);

    root = delete_avl(root, 30); // Deleting a leaf

    TEST_CHECK(search_avl(root, 30) == NULL);
    TEST_CHECK(search_avl(root, 50) != NULL);
    TEST_CHECK(search_avl(root, 70) != NULL);
    destroy_avl(root);
}

void test_deletion_one_child(void) {
    avl *root = NULL;
    root = insert_avl(root, 50);
    root = insert_avl(root, 30);
    root = insert_avl(root, 20); // 30 has only one left child

    root = delete_avl(root, 30); // delete node with one child

    TEST_CHECK(search_avl(root, 30) == NULL);
    TEST_CHECK(search_avl(root, 20) != NULL);
    TEST_CHECK(search_avl(root, 50) != NULL);
    destroy_avl(root);
}

void test_deletion_two_children(void) {
    avl *root = NULL;
    root = insert_avl(root, 40);
    root = insert_avl(root, 20);
    root = insert_avl(root, 60);
    root = insert_avl(root, 10);
    root = insert_avl(root, 30);
    root = insert_avl(root, 50);
    root = insert_avl(root, 70);

    root = delete_avl(root, 40); // node with two children

    TEST_CHECK(search_avl(root, 40) == NULL);
    TEST_CHECK(search_avl(root, 30) != NULL);
    TEST_CHECK(search_avl(root, 50) != NULL);
    TEST_CHECK(search_avl(root, 60) != NULL);
    TEST_CHECK(get_height(root) > 0);
    destroy_avl(root);
}

TEST_LIST = {
    {"Insert and Search", test_insert_and_search},
    {"Balancing (rotations)", test_balancing},
    {"Delete Leaf Node", test_deletion_leaf},
    {"Delete Node with One Child", test_deletion_one_child},
    {"Delete Node with Two Children", test_deletion_two_children},
    {NULL, NULL}
};
