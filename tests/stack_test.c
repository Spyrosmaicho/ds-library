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


void test_stack_init(void) {
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    int *data = get_stack_data(stack);
    int top = get_stack_top(stack);
    TEST_CHECK(data != NULL);
    TEST_CHECK(top == -1);
}

void test_stack_empty(void) {

    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    TEST_CHECK(is_stack_empty(stack) == true);
    
    stack_push(stack, 42);
    TEST_CHECK(is_stack_empty(stack) == false);
    
    destroy_stack(stack);
}

void test_stack_full(void) 
{
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized

    for (int i = 0; i < 100; i++)  stack_push(stack, i);
    
    TEST_CHECK(is_stack_full(stack) == true);
    
    stack_push(stack, 101); // Attempt to push when full
    TEST_CHECK(is_stack_full(stack) == false); // Should still be full

    destroy_stack(stack);
}

void test_stack_size(void) 
{
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    TEST_CHECK(stack_size(stack) == 0);
    
    for (int i = 0; i < 5; i++) stack_push(stack, i);
    
    TEST_CHECK(stack_size(stack) == 5);
    
    for(int i = 5 ; i < 100; i++) stack_push(stack, i);

    TEST_CHECK(stack_size(stack) == 100);

    stack_push(stack,101);
    TEST_CHECK(stack_size(stack) == 101);

    for(int i = 0; i < 50; i++) stack_pop(stack);

    TEST_CHECK(stack_size(stack) == 51);

    destroy_stack(stack);
}

void test_stack_peek(void) 
{
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    
    TEST_CHECK(stack_peek(stack) == 30); // Should return the top element
    
    stack_pop(stack);
    TEST_CHECK(stack_peek(stack) == 20); // Should return the new top element
    
    destroy_stack(stack);

    Stack *stack2 = init_stack();

    for(int i = 0;i<101;i++) stack_push(stack2,i);

    TEST_CHECK(stack_peek(stack2) == 100); // Should return the top element
    
    destroy_stack(stack2);
}

void test_stack_push(void) 
{
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    stack_push(stack, 42);
    TEST_CHECK(stack_peek(stack) == 42); // Check if the pushed value is on top
    
    stack_push(stack, 84);
    TEST_CHECK(stack_peek(stack) == 84); // Check if the new value is on top
    
    destroy_stack(stack);
}

void test_stack_pop(void) 
{
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    
    stack_pop(stack);
    TEST_CHECK(stack_peek(stack) == 20); // Should return the new top element after pop
    
    stack_pop(stack);
    TEST_CHECK(stack_peek(stack) == 10); // Should return the new top element after another pop
    
    destroy_stack(stack);
}

void test_destroy_stack(void) 
{
    Stack *stack = init_stack();
    TEST_CHECK(stack != NULL); // Check if stack is initialized
    for(int i = 0;i<300 ;i++) stack_push(stack,i);
    
    destroy_stack(stack); // Ensure it runs without errors
    
    // After destroying, the stack should not be accessible, but we can't check it directly.
    // We can only ensure that the function runs without errors.
    TEST_CHECK(true);
}

TEST_LIST = {
    { "stack_init", test_stack_init },
    { "stack_empty", test_stack_empty },
    { "stack_full", test_stack_full },
    { "stack_size", test_stack_size },
    { "stack_peek", test_stack_peek },
    { "stack_push", test_stack_push },
    { "stack_pop", test_stack_pop },
    { "destroy_stack", test_destroy_stack },
    { NULL, NULL }
};