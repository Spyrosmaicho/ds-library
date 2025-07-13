#include <stdlib.h>
#include "stack.h"

struct Stack 
{
    int *data;      // Pointer to the stack's data
    int top;        // Index of the top element
    int capacity;  // Capacity of the stack
};


/*Function to initialize a stack*/
Stack *init_stack(void)
{
    Stack *stack = malloc(sizeof(struct Stack));
    if(!stack) return NULL; // If memory allocation fails, return

    stack->capacity = 100; // Set initial capacity
    stack->data = malloc(stack->capacity * sizeof(int)); // Allocate memory for 100 integers
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
int stack_peek(Stack *stack)
{
    if (is_stack_empty(stack)) return -1; // Return -1 if the stack is empty

    return stack->data[stack->top]; // Return the top element of the stack
}

/*Function to push an element onto the stack*/
void stack_push(Stack *stack,int val)
{
    if(!stack || is_stack_full(stack))
    {
        int *new_data = realloc(stack->data, (stack->capacity*2) * sizeof(int));
        if(!new_data) return;

        stack->data = new_data; // Reallocate memory to double the capacity
        stack->capacity *= 2; // Update the capacity
    }

    stack->data[++stack->top] = val; // Increment top and push the value onto the stack
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
int *get_stack_data(Stack *stack)
{
    return stack->data;
}
// Helper function to get the index of the top element
int get_stack_top(Stack *stack)
{
    if(!stack || stack->top==-1) return -1;

    return stack->top; // Return the index of the top element
}