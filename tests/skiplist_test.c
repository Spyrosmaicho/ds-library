#include "skiplist.h"
#include <stdio.h>

//Helper function for printing
void print_line() 
{
    printf("\n------------------------------------------\n");
}

//Helper function to print N. Useful for testing
void print_N(char* label, SkipList *list) {
    printf("%s Size: %d\n", label, STcount(list));
}

//test case for search
void test_case_search_missing(SkipList *list) 
{
    printf("\nSearching for non-existent student 999:\n");
    Value *v = STsearch(list, 999);
    printf("Student 999 grade: %s\n", v ? "Found (unexpected!)" : "Missing (correct)");
}

//Test case to delete a node
void test_case_delete_missing(SkipList *list) 
{
    printf("\nAttempting to delete non-existent student 888:\n");
    STdelete(list, 888);
    print_N("After attempted deletion", list);
}

//Test case for insert
void test_case_duplicate_insert(SkipList **list) {

    printf("\nInserting student 103 with same grade (78):\n");
    STinsert(*list, 103, 78);
    print_N("After duplicate insert", *list);
    STprint(*list);
}

//Test case for merge
void test_merge_operation(SkipList **list1, SkipList *list2) 
{
    printf("\nTesting merge operation:\n");
    
    printf("Before merge:\n");
    printf("Main List:\n");
    STprint(*list1);
    print_N("Main list count", *list1);
    
    printf("\nSecond List:\n");
    STprint(list2);
    print_N("Second list count", list2);
    
    //Perform merge
    SkipList *merged = STmerge(*list1, list2);
    STdestroy(*list1);
    *list1 = merged;
    
    printf("\nAfter merge:\n");
    printf("Main List (should contain merged items):\n");
    STprint(*list1);
    print_N("Main list count", *list1);
    
    printf("\nSecond List (should be empty):\n");
    STprint(list2);
    print_N("Second list count", list2);
}

int main() 
{
    //Initialize main skip list
    SkipList *list1 = STinit(lgNmax);
    SkipList *list2 = STinit(lgNmax);
    
    //Insert initial data
    STinsert(list1, 101, 85);
    STinsert(list1, 102, 90);
    STinsert(list1, 103, 78);

    //Insert data into second list
    STinsert(list2, 102, 95);  //Duplicate key
    STinsert(list2, 104, 88);
    STinsert(list2, 105, 82);

    print_line();
    printf("Initial Student Records");
    print_line();
    STprint(list1);
    print_N("Initial list", list1);

    //Search test
    print_line();
    printf("Search Operations");
    print_line();
    
    Value *v = STsearch(list1, 102);
    
    printf("Student 102 grade: %s\n", v ? "Found" : "Missing");
    if(v) printf("Actual grade: %d\n", *v);

    //Delete test
    printf("\nDeleting student 103:\n");
    if(STdelete(list1, 103))
    {
        print_N("After deletion", list1);
        STprint(list1);
    }
    else printf("Nothing deleted\n");

    //Additional test cases
    print_line();
    printf("Additional Test Cases");
    print_line();
    
    test_case_search_missing(list1);
    test_case_delete_missing(list1);
    test_case_duplicate_insert(&list1);

    //Merge operation test
    print_line();
    printf("Merge Operation Test");
    print_line();
    test_merge_operation(&list1, list2);

    //Cleanup memory
    STdestroy(list1);
    STdestroy(list2);
    
    return 0;
}