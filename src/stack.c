#include <stdlib.h>
#include "stack.h"
#include <string.h>

struct Stack 
{
    void *data;      // Pointer to the stack's data
    int top;        // Index of the top element
    int element_size; // Size of each element in the stack
    int capacity;  // Capacity of the stack
};


/*Function to initialize a stack*/
Stack *init_stack(int element_size)
{
    Stack *stack = malloc(sizeof(struct Stack));
    if(!stack) return NULL; // If memory allocation fails, return

    stack->capacity = 100; // Set initial capacity
    stack->element_size = element_size; // Set the size of each element
    stack->data = malloc(stack->capacity * stack->element_size); // Allocate memory for 100 integers
    if(!stack->data) 
    {
        free(stack); // Free the stack if data allocation fails
        return NULL;
    }

    stack->top = -1; // Initialize top to -1 indicating the stack is empty
    return stack;
}

/*Function to check if the stack is empty*/
bool is_stack_empty(Stack *stack)
{
    return stack->top == -1; // Return true if top is -1, indicating the stack is empty
}

/*Function to check if the stack is full*/
bool is_stack_full(Stack *stack)
{
    return stack && (stack->top + 1 >= stack->capacity); // Return true if top is at or exceeds capacity
}

/*Function to return the size of the stack*/
int stack_size(Stack *stack)
{
    return stack->top + 1; // Return the number of elements in the stack
}

/*Function to return the topmost element of the stack*/
void *stack_peek(Stack *stack)
{
    if (!stack || is_stack_empty(stack)) return NULL; // Return NULL if the stack is empty

    return (char*)stack->data + stack->top * stack->element_size; // Return the top element of the stack
}

/*Function to push an element onto the stack*/
void stack_push(Stack *stack,void *val)
{
    if(!stack || is_stack_full(stack))
    {
        void *new_data = realloc(stack->data, (stack->capacity*2) *stack->element_size);
        if(!new_data) return;

        stack->data = new_data; // Reallocate memory to double the capacity
        stack->capacity *= 2; // Update the capacity
    }

    stack->top++; // Increment top to point to the next position
    char *ptr = (char*)stack->data + stack->top * stack->element_size; // Calculate the address of the new top element
    memcpy(ptr,val, stack->element_size); // Copy the value into the stack
}

/*Function to pop an element from the stack*/
void stack_pop(Stack *stack)
{
    if(!stack || is_stack_empty(stack)) return; // If stack is null or empty, do nothing

    stack->top--;
}

/*Function to destroy the stack and free memory*/
void destroy_stack(Stack *stack)
{
    if(!stack) return;

    free(stack->data);
    free(stack); // Free the memory allocated for the stack and its data
}

//Helper function to get the stack data
void *get_stack_data(Stack *stack)
{
    return stack->data;
}
// Helper function to get the index of the top element
int get_stack_top(Stack *stack)
{
    if(!stack || stack->top==-1) return -1;

    return stack->top; // Return the index of the top element
}

//Helper function to get the capacity of the stack
int get_stack_capacity(Stack *stack)
{
    if(!stack) return -1;
    return stack->capacity; // Return the capacity of the stack
}