#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

/*Function to initialize a stack*/
Stack *init_stack(int element_size);

/*Function to check if the stack is empty*/
bool is_stack_empty(Stack *stack);

/*Function to check if the stack is full*/
bool is_stack_full(Stack *stack);

/*Function to return the size of the stack*/
int stack_size(Stack *stack);

/*Function to return the topmost element of the stack*/
void *stack_peek(Stack *stack);

/*Function to push an element onto the stack*/
void stack_push(Stack *stack,void *val);

/*Function to pop an element from the stack*/
void stack_pop(Stack *stack);

/*Function to destroy the stack and free memory*/
void destroy_stack(Stack *stack);

// Helper function to get the index of the top element
int get_stack_top(Stack *stack);

//Helper function to get the stack data
void *get_stack_data(Stack *stack);

//Helper function to get the capacity of the stack
int get_stack_capacity(Stack *stack);

#endif