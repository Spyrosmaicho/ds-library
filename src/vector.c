#include <stdlib.h>
#include "vector.h"
#include <string.h>

struct vector
{
    void *data;
    int element_size;
    int capacity;
    int index;
};

/*Function to initialize a dynamic array*/
vector  *init(int el_size,int size)
{
    vector *array = malloc(sizeof(struct vector));
    if(!array) return NULL;
    array->capacity = size;
    array->element_size = el_size;
    array->data = malloc(array->capacity * array->element_size);
    if(!array->data) 
    {
        free(array);
        return NULL;
    }
    array->index = -1;
    return array;
}

/*Function to check if the array is empty*/
bool empty(vector *array)
{
    return array && array->index <= -1;
}

/*Function to check if the array is full*/
bool full(vector *array)
{
    return array && (array->capacity - 1 == array->index);
}

/*Function to return how many elements the array has*/
int elements(vector *array)
{
    return array->index + 1;
}

/*Function to insert an item into the dynamic array*/
void insert(void *value,vector *array)
{
    if(!array || full(array))
    {
        void *new_data = realloc(array->data,(array->capacity*2) * array->element_size);
        if(!new_data) return;

        array->data = new_data;
        array->capacity *=2;
    }
    array->index++;
    char *pointer = (char*)array->data + array->index * array->element_size;
    memcpy(pointer,value,array->element_size);
}

/*Function to get a specific value of the array*/
void *get_value(void *target,vector *array,Compare cmp)
{
    if(!array || empty(array)) return NULL;

    for(int i = 0 ;i< array->index+1;i++)
    {
        char *current = (char*)array->data + i * array->element_size;
        if(cmp(current,target)==0) return current;
    }

    return NULL;
}

/*Function to return the last item of the dynamic array*/
void *peek(vector *array)
{
    if(!array || empty(array)) return NULL;

    return (char*)array->data + array->index * array->element_size;
}

/*Function to deallocate all the memory we allocated for the aray*/
void destroy(vector *array)
{
    if(!array) return;

    free(array->data);
    free(array);
}


//Helper function to get the current index of the array
int get_index(vector *v)
{
    if(!v) return -1;
    return v->index;
}

//Helper function to get the data of the struct Vector
void *get_data(vector *v)
{
    if(!v) return NULL;
    
    return v->data;
}

//Helper function to get the capacity of the array
int get_capacity(vector *v)
{
    if(!v) return 0;

    return v->capacity;
}