#include "queue.h"
#include "../acutest/acutest.h"
#include <stdlib.h>
#include <string.h>

/**
 *  All tests have been updated for the generic queue implementation
 *  that supports any data type through void pointers.
 */

void test_queue_init(void) 
{
    Queue *queue = init_queue(sizeof(int));
    TEST_CHECK(queue != NULL);
    TEST_CHECK(queue_size(queue) == 0);
    TEST_CHECK(is_queue_empty(queue) == true);
    TEST_CHECK(is_queue_full(queue) == false);
    free_queue(queue);
}

void test_int_queue(void) 
{
    Queue *queue = init_queue(sizeof(int));
    TEST_CHECK(queue != NULL);
    
    int values[] = {10, 20, 30, 40, 50};
    
    // Test enqueue with integers
    for (int i = 0; i < 5; i++) {
        enqueue(queue, &values[i]);
    }
    TEST_CHECK(queue_size(queue) == 5);
    TEST_CHECK(is_queue_empty(queue) == false);
    
    // Test peek with integers
    int *front = queue_peek(queue);
    TEST_CHECK(*front == 10);
    
    // Test dequeue with integers
    dequeue(queue);
    front = queue_peek(queue);
    TEST_CHECK(*front == 20);
    TEST_CHECK(queue_size(queue) == 4);
    
    free_queue(queue);
}

void test_struct_queue(void)
{
    typedef struct {
        int id;
        char name[20];
        float score;
    } Student;
    
    Queue *queue = init_queue(sizeof(Student));
    TEST_CHECK(queue != NULL);
    
    Student s1 = {1, "Alice", 85.5f};
    Student s2 = {2, "Bob", 92.0f};
    
    // Test enqueue with structs
    enqueue(queue, &s1);
    enqueue(queue, &s2);
    TEST_CHECK(queue_size(queue) == 2);
    
    // Test peek with structs
    Student *front = queue_peek(queue);
    TEST_CHECK(front->id == 1);
    TEST_CHECK(strcmp(front->name, "Alice") == 0);
    TEST_CHECK(front->score == 85.5f);
    
    // Test dequeue with structs
    dequeue(queue);
    front = queue_peek(queue);
    TEST_CHECK(front->id == 2);
    
    free_queue(queue);
}

void test_queue_resizing(void) 
{
    Queue *queue = init_queue(sizeof(int));
    TEST_CHECK(queue != NULL);
    
    // Fill the queue beyond initial capacity
    for (int i = 0; i < 150; i++) {
        enqueue(queue, &i);
    }
    TEST_CHECK(queue_size(queue) == 150);
    TEST_CHECK(get_queue_capacity(queue) >= 150);
    
    // Verify elements are correct after resizing
    int *front = queue_peek(queue);
    TEST_CHECK(*front == 0);
    
    for (int i = 0; i < 100; i++) {
        dequeue(queue);
    }
    front = queue_peek(queue);
    TEST_CHECK(*front == 100);
    TEST_CHECK(queue_size(queue) == 50);
    
    free_queue(queue);
}

void test_queue_edge_cases(void)
{
    // Test with char type
    Queue *char_queue = init_queue(sizeof(char));
    char c = 'A';
    enqueue(char_queue, &c);
    char *char_front = queue_peek(char_queue);
    TEST_CHECK(*char_front == 'A');
    free_queue(char_queue);
    
    // Test with double type
    Queue *double_queue = init_queue(sizeof(double));
    double d = 3.14159;
    enqueue(double_queue, &d);
    double *double_front = queue_peek(double_queue);
    TEST_CHECK(*double_front == d);
    free_queue(double_queue);
    
    // Test empty queue peek
    Queue *empty_queue = init_queue(sizeof(int));
    TEST_CHECK(queue_peek(empty_queue) == NULL);
    free_queue(empty_queue);
}

TEST_LIST = {
    { "queue_init", test_queue_init },
    { "int_queue", test_int_queue },
    { "struct_queue", test_struct_queue },
    { "queue_resizing", test_queue_resizing },
    { "queue_edge_cases", test_queue_edge_cases },
    { NULL, NULL }
};