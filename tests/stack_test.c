#include "stack.h"
#include "../acutest/acutest.h"
#include <stdlib.h>

#include <stdlib.h>
/**
 *  All tests have been made in a way to showcase
 *  the effectiveness of every function implemented.
 *  Please review the code for every test to understand
 *  the cases it covers.
*/


void test_stack_init(void) 
{
    Stack *stack = init_stack(sizeof(int));
    TEST_CHECK(stack != NULL);
    TEST_CHECK(stack_size(stack) == 0);
    TEST_CHECK(is_stack_empty(stack) == true);
    TEST_CHECK(is_stack_full(stack) == false);
    destroy_stack(stack);
}

void test_int_stack(void) 
{
    Stack *stack = init_stack(sizeof(int));
    TEST_CHECK(stack != NULL);
    
    int values[] = {10, 20, 30, 40, 50};
    
    // Test push with integers
    for (int i = 0; i < 5; i++) {
        stack_push(stack, &values[i]);
    }
    TEST_CHECK(stack_size(stack) == 5);
    TEST_CHECK(is_stack_empty(stack) == false);
    
    // Test peek with integers
    int *top = stack_peek(stack);
    TEST_CHECK(*top == 50);
    
    // Test pop with integers
    stack_pop(stack);
    top = stack_peek(stack);
    TEST_CHECK(*top == 40);
    TEST_CHECK(stack_size(stack) == 4);
    
    destroy_stack(stack);
}

void test_struct_stack(void)
{
    typedef struct {
        int id;
        char name[20];
        float score;
    } Student;
    
    Stack *stack = init_stack(sizeof(Student));
    TEST_CHECK(stack != NULL);
    
    Student s1 = {1, "Alice", 85.5f};
    Student s2 = {2, "Bob", 92.0f};
    
    // Test push with structs
    stack_push(stack, &s1);
    stack_push(stack, &s2);
    TEST_CHECK(stack_size(stack) == 2);
    
    // Test peek with structs
    Student *top = stack_peek(stack);
    TEST_CHECK(top->id == 2);
    TEST_CHECK(strcmp(top->name, "Bob") == 0);
    TEST_CHECK(top->score == 92.0f);
    
    // Test pop with structs
    stack_pop(stack);
    top = stack_peek(stack);
    TEST_CHECK(top->id == 1);
    
    destroy_stack(stack);
}

void test_stack_resizing(void) 
{
    Stack *stack = init_stack(sizeof(int));
    TEST_CHECK(stack != NULL);
    
    // Fill the stack beyond initial capacity
    for (int i = 0; i < 150; i++) {
        stack_push(stack, &i);
    }
    TEST_CHECK(stack_size(stack) == 150);
    int capacity = get_stack_capacity(stack);
    TEST_CHECK(capacity >= 150);
    
    // Verify elements are correct after resizing
    int *top = stack_peek(stack);
    TEST_CHECK(*top == 149);
    
    for (int i = 0; i < 100; i++) {
        stack_pop(stack);
    }
    top = stack_peek(stack);
    TEST_CHECK(*top == 49);
    TEST_CHECK(stack_size(stack) == 50);
    
    destroy_stack(stack);
}

void test_stack_edge_cases(void)
{
    // Test with char type
    Stack *char_stack = init_stack(sizeof(char));
    char c = 'A';
    stack_push(char_stack, &c);
    char *char_top = stack_peek(char_stack);
    TEST_CHECK(*char_top == 'A');
    destroy_stack(char_stack);
    
    // Test with double type
    Stack *double_stack = init_stack(sizeof(double));
    double d = 3.14159;
    stack_push(double_stack, &d);
    double *double_top = stack_peek(double_stack);
    TEST_CHECK(*double_top == d);
    destroy_stack(double_stack);
    
    // Test empty stack operations
    Stack *empty_stack = init_stack(sizeof(int));
    TEST_CHECK(stack_peek(empty_stack) == NULL);
    stack_pop(empty_stack);  // Should not crash
    destroy_stack(empty_stack);
    
    // Test get_stack_data and get_stack_top
    Stack *test_stack = init_stack(sizeof(int));
    int val = 42;
    stack_push(test_stack, &val);
    TEST_CHECK(get_stack_data(test_stack) != NULL);
    TEST_CHECK(get_stack_top(test_stack) == 0);
    destroy_stack(test_stack);
}

TEST_LIST = {
    { "stack_init", test_stack_init },
    { "int_stack", test_int_stack },
    { "struct_stack", test_struct_stack },
    { "stack_resizing", test_stack_resizing },
    { "stack_edge_cases", test_stack_edge_cases },
    { NULL, NULL }
};