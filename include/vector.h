#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef int (*Compare)(const void *a,const void *b);
typedef struct vector vector;

/*Function to initialize a dynamic array*/
vector  *init(int el_size,int size);

/*Function to insert an item into the dynamic array*/
void insert(void *value,vector *array);

/*Function to check if the array is full*/
bool full(vector *array);

/*Function to check if the array is empty*/
bool empty(vector *array);

/*Function to return the last item of the dynamic array*/
void *peek(vector *array);

/*Function to return how many elements the array has*/
int elements(vector *array);

/*Function to get a specific value of the array*/
void *get_value(void *target,vector *array,Compare cmp);

/*Function to deallocate all the memory we allocated for the aray*/
void destroy(vector *array);

//Helper function to get the current index of the array
int get_index(vector *v);

//Helper function to get the data of the struct Vector
void *get_data(vector *v);

//Helper function to get the capacity of the array
int get_capacity(vector *v);

#endif