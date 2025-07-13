#include <stdlib.h>
#include "list.h"
#include <stdio.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct List 
{
    struct ListNode *head;
    int size;
};

enum Status 
{
    FAILURE = 0,
    SUCCESS = 1
};

/*Function that creates a List struct*/
List *create_list(void)
{
    List *list = malloc(sizeof(struct List));
    if(!list) return NULL; // If memory allocation fails, return NULL

    list->head = NULL; // Initialize head to NULL
    list->size = 0; // Initialize size to 0
    return list;
}

/*Function that creates a List Node*/
Node *create_node(int data)
{
    Node *node = malloc(sizeof(struct ListNode));
    if(!node) return NULL;

    node->val = data;
    node->next = NULL;
    return node;
}

/*Function that returns the size(number of elements) in the list*/
int list_size(List *head)
{
    return head ? head->size : 0; // Return size of the list, or 0 if the list is NULL
}

/*Function that checks if the list is empty*/
bool list_empty(List *head)
{
    return (head == NULL || head->size == 0); // Check if the list is NULL or has no elements
}

/*Function that adds a node at the end of the list*/
void add_node(List *list,int data)
{
    Node *new_node = create_node(data);
    if(!new_node) return; // If memory allocation fails, return NULL

    if(!list->head) 
    {
        list->head = new_node; // If the list is empty, set the new node as head
        list->size = 1; // Set size to 1
        return; 
    }
    Node *temp = list->head;
    while(temp->next) // Traverse to the end of the list
    {
        temp = temp->next;
    }
    temp->next = new_node; // Link the new node at the end
    list->size++; // Increment size of the list
}

/*Function that searches for a value in the linked list*/
bool search_list(List *list, int value)
{
    if(list->head)
    {
        Node *temp = list->head;
        while(temp)
        {
            if(temp->val == value)
            {
                return true; // Value found
            }
            temp = temp->next; // Move to the next node
        }
    }
    return false; // Value not found
}

/*Function that frees only one node with a specific value*/
void free_node(List *list, int value)
{
    if(list->head)
    {
        if(search_list(list,value))
        {
            Node *temp = list->head;
            Node *prev = NULL;

            while(temp && temp->val != value)
            {
                prev = temp;
                temp = temp->next;
            }

            if (!prev) list->head = temp->next; // If the node to be deleted is the head
            else  prev->next = temp->next;
            free(temp);
            list->size--; // Decrement size after freeing the node
        }
    }
}

/*Function that frees the list*/
void free_list(List *list)
{
    if(list->head)
    {
        for(int i = 0; i < list->size; i++)
        {
            Node *temp = list->head;
            list->head = list->head->next;
            free(temp);
        }
    }
    list->size = 0; // Reset size to 0
    list->head = NULL; // Set the head to NULL after freeing the list
    free(list); // Free the list structure itself
}



/* Function that prints list */
void print_list(List *list) 
{
    if (list_empty(list)) 
    {
        printf("List is empty.\n");
        return;
    }
    
    
    Node *current = list->head;
    printf("[");
    for(int i = 0; i < list->size; i++) 
    {
        printf("%d", current->val);
        if (current->next) 
        {
            printf(", ");
        }
        current = current->next;
    }
    
    printf("]\n");
}


//Helper function to get the head of the list
Node *get_head(List *list)
{
    if(list && list->head) return list->head; // Return the head of the list if it exists
    return NULL; // Return NULL if the list is NULL or has no head  
}