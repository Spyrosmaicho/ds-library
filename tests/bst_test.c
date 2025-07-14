#include "bst.h"
#include "../acutest/acutest.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
        int id;
        char name[20];
    } Person;

int cmp(const void *a,const void *b)
{
    return *(int*)a - *(int*)b;
}

int string_cmp(const void *a,const void*b)
{
    return strncmp((char*)a,(char*)b,20);
}

int struct_cmp(const void *a,const void *b)
{
    const Person *pa = a;
    const Person *pb = b;
    if (pa->id != pb->id) return pa->id - pb->id;
    return strncmp(pa->name, pb->name, 20);
}
void test_bst_init(void) {
    BST *bst = init_bst(sizeof(int));
    TEST_CHECK(bst != NULL);
    void *val = bst_val(bst);
    BST *left = bst_left(bst);
    BST *right = bst_right(bst);
    int size = bst_element_size(bst);
    TEST_CHECK(val == NULL);
    TEST_CHECK(left == NULL);
    TEST_CHECK(right == NULL);
    TEST_CHECK(size == sizeof(int));
    free_bst(bst);
}

void test_int_bst(void) {
    BST *bst = init_bst(sizeof(int));
    
    // Test insertion
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) bst_insert(bst, &values[i],cmp);
    
    // Test search for existing values
    TEST_CHECK(bst_search(bst, &values[0],cmp) == true);  // 50
    TEST_CHECK(bst_search(bst, &values[3],cmp) == true);  // 20
    TEST_CHECK(bst_search(bst, &values[6],cmp) == true);  // 80
    
    // Test search for non-existing values
    int not_exists = 100;
    TEST_CHECK(bst_search(bst, &not_exists,cmp) == false);
    
    // Test deletion
    TEST_CHECK(delete_bst(&bst, &values[2],cmp) == true);  // Delete 70
    TEST_CHECK(bst_search(bst, &values[2],cmp) == false);  // 70 should not exist
    
    // Verify tree structure after deletion
    TEST_CHECK(bst_search(bst, &values[5],cmp) == true);   // 60 should still exist
    
    free_bst(bst);
}

void test_struct_bst(void) {
    
    BST *bst = init_bst(sizeof(Person));
    
    Person p1 = {1, "Alice"};
    Person p2 = {2, "Bob"};
    Person p3 = {3, "Charlie"};
    
    // Test insertion
    bst_insert(bst, &p1,struct_cmp);
    bst_insert(bst, &p2,struct_cmp);
    bst_insert(bst, &p3,struct_cmp);
    
    // Test search
    TEST_CHECK(bst_search(bst, &p1,struct_cmp) == true);
    TEST_CHECK(bst_search(bst, &p2,struct_cmp) == true);
    
    // Test deletion
    TEST_CHECK(delete_bst(&bst, &p2,struct_cmp) == true);
    TEST_CHECK(bst_search(bst, &p2,struct_cmp) == false);
    
    free_bst(bst);
}

void test_edge_cases(void) {
    // Test empty BST
    BST *empty_bst = init_bst(sizeof(int));
    int val = 42;
    TEST_CHECK(bst_search(empty_bst, &val,cmp) == false);
    TEST_CHECK(delete_bst(&empty_bst, &val,cmp) == false);
    free_bst(empty_bst);
    
    // Test NULL cases
    TEST_CHECK(bst_search(NULL, &val,cmp) == false);
    TEST_CHECK(delete_bst(NULL, &val,cmp) == false);
    
    // Test single node BST
    BST *single_bst = init_bst(sizeof(int));
    bst_insert(single_bst, &val,cmp);
    TEST_CHECK(bst_search(single_bst, &val,cmp) == true);
    TEST_CHECK(delete_bst(&single_bst, &val,cmp) == true);
    free_bst(single_bst);
}

void test_string_bst(void) {
    BST *bst = init_bst(sizeof(char[20]));
    
    char names[][20] = {"apple", "banana", "cherry", "date"};
    
    // Test insertion
    for (int i = 0; i < 4; i++) bst_insert(bst, names[i],string_cmp);
    
    // Test search
    TEST_CHECK(bst_search(bst, "banana",string_cmp) == true);
    TEST_CHECK(bst_search(bst, "date",string_cmp) == true);
    
    // Test non-existing
    TEST_CHECK(bst_search(bst, "fig",string_cmp) == false);
    
    // Test deletion
    TEST_CHECK(delete_bst(&bst, "cherry",string_cmp) == true);
    TEST_CHECK(bst_search(bst, "cherry",string_cmp) == false);
    
    free_bst(bst);
}

void test_deletion_scenarios(void) {
    BST *bst = init_bst(sizeof(int));
    
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        bst_insert(bst, &values[i],cmp);
    }
    
    // Case 1: Delete leaf node (20)
    TEST_CHECK(delete_bst(&bst, &values[3],cmp) == true);
    TEST_CHECK(bst_search(bst, &values[3],cmp) == false);
    
    // Case 2: Delete node with one child (70 which now should have only 80)
    TEST_CHECK(delete_bst(&bst, &values[2],cmp) == true);
    TEST_CHECK(bst_search(bst, &values[2],cmp) == false);
    TEST_CHECK(bst_search(bst, &values[6],cmp) == true);  // 80 should still exist
    
    // Case 3: Delete node with two children (50)
    TEST_CHECK(delete_bst(&bst, &values[0],cmp) == true);
    TEST_CHECK(bst_search(bst, &values[0],cmp) == false);
    
    free_bst(bst);
}

TEST_LIST = {
    { "bst_init", test_bst_init },
    { "int_bst", test_int_bst },
    { "struct_bst", test_struct_bst },
    { "edge_cases", test_edge_cases },
    { "string_bst", test_string_bst },
    { "deletion_scenarios", test_deletion_scenarios },
    { NULL, NULL }
};