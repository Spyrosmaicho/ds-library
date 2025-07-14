#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
#include <string.h>

/*Hidden struct from user*/
struct Queue
{
    void *arr;
    int front;
    int rear;
    int capacity;
    int element_size; // Size of each element in the queue, if needed
};

/*Function to initialize a queue*/
Queue *init_queue(int element_size)
{
    Queue *queue = malloc(sizeof(Queue));
    if(!queue) return NULL; // If memory allocation fails, return NULL

    queue->capacity = 100; // Set initial capacity
    queue->element_size = element_size; // Set the size of each element
    queue->arr = malloc(queue->capacity * queue->element_size); // Allocate memory for 100 integers
    if(!queue->arr) 
    {
        free(queue); // Free the queue if data allocation fails
        return NULL;    
    }
    queue->front = 0; // Initialize front to 0
    queue->rear = 0; // Initialize rear to 0
    return queue;
}

/*Function to return how many elements are in the queue*/
int queue_size(Queue * queue)
{
    if(!queue || is_queue_empty(queue)) return 0; // If queue is NULL or empty, return 0
    return queue->rear - queue->front; // Return the number of elements in the queue
}

/*Function to check if queue is empty*/
bool is_queue_empty(Queue *queue)
{
    return queue->front == queue->rear; // Return true if front is -1, indicating the queue is empty
}

/*Function to check if queue is full*/
bool is_queue_full(Queue *queue)
{
    //printf("Queue full check: front = %d, rear = %d, capacity = %d\n", queue->front, queue->rear, queue->capacity);
    return queue && (queue->rear >= queue->capacity); // Return true if rear exceeds capacity
}

/*Function to add an element into the queue*/
void enqueue(Queue *queue,void *value)
{
    if(!queue) return; // If queue is NULL, return NULL

    if (queue->front > queue->capacity / 3) 
    {
        char *new_arr = (char*)queue->arr + queue->front * queue->element_size;
        memmove(queue->arr,new_arr, queue_size(queue) * queue->element_size); // Move elements to the start of the array
        queue->rear -= queue->front; // Adjust rear to reflect the new position
        queue->front = 0; // Reset front to 0
    }

    if(is_queue_full(queue)) 
    {
        void *new_data = realloc(queue->arr, queue->capacity * 2 * sizeof(int));
        if(!new_data) return; // If realloc fails, do nothing
        queue->arr = new_data; // Update the array pointer to the new memory
        queue->capacity *= 2; // Double the capacity 
    }

    if(is_queue_empty(queue)) 
    {
        queue->front = 0; // Set front to 0 if queue was empty
        queue->rear = 0; // Set rear to 0
    }

    char *curr = (char*)queue->arr + queue->rear * queue->element_size; // Get the current position to insert the new element
    memcpy(curr, value, queue->element_size); // Copy the new element into the queue
    queue->rear++; // Increment rear to point to the next position 
}

/*Function to remove an element from the queue*/
void dequeue(Queue *queue)
{
    if(!queue || is_queue_empty(queue)) return; // If queue is NULL or empty, do nothing
    queue->front++; // Increment front to remove the element

    if(queue->front >= queue->rear) queue->front = 0,queue->rear = 0; // Reset front and rear if queue becomes empty
}

/*Function to free a queue*/
void free_queue(Queue *queue)
{
    if(queue)
    {
        free(queue->arr);
        free(queue);
        queue = NULL; // Set queue to NULL after freeing to avoid dangling pointer
    }

}

//Helper function to get the capacity of the queue
int get_queue_capacity(Queue *queue)
{
    if(!queue) return 0; // If queue is NULL, return 0
    return queue->capacity; // Return the current capacity of the queue
}

// Function to get the element at the front of the queue
void *queue_peek(Queue *queue)
{
    if(!queue || is_queue_empty(queue)) return NULL; // If queue is NULL or empty, return -1
    return (char*)queue->arr + queue->front * queue->element_size; // Return the front element
}