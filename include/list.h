#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct List List;
typedef struct ListNode Node;

/*Function that creates a List struct*/
List *create_list(void);

/*Function that creates a List Node*/
Node *create_node(int data);

/*Function that adds a node at the end of the list*/
void add_node(List *node,int data);

/*Function that returns the size(number of elements) in the list*/
int list_size(List *list);

/*Function that checks if the list is empty*/
bool list_empty(List *list);

/*Function that searches for a value in the linked list*/
bool search_list(List *list, int value);

/*Function that frees only one node with a specific value*/
void free_node(List *node, int value);

/*Function that frees the list*/
void free_list(List *node);

/* Function that prints list */
void print_list(List *list);

//Helper function to get the head of the list
Node *get_head(List *list);

#endif 