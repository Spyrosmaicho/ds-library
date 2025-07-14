#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct Queue Queue;

/*Function to initialize a queue*/
Queue *init_queue(int element_size);

/*Function to return how many elements are in the queue*/
int queue_size(Queue * queue);

/*Function to check if queue is empty*/
bool is_queue_empty(Queue *queue);

/*Function to check if queue is full*/
bool is_queue_full(Queue *queue);

/*Function to add an element into the queue*/
void enqueue(Queue *queue,void *value);

/*Function to remove an element from the queue*/
void dequeue(Queue *queue);

/*Function to free a queue*/
void free_queue(Queue *queue);

//Helper function to get the capacity of the queue
int get_queue_capacity(Queue *queue);

// Function to get the element at the front of the queue
void *queue_peek(Queue *queue);

#endif