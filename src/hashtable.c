#include <stdlib.h>
#include "hashtable.h"
#include <string.h>


/*Hidden structs from user*/

struct hashnode
{
    char *key;
    int value;
    struct hashnode* next;
};

struct hashtable
{
    int cnt;
    int size;
    struct hashnode **bucket;
};

//Helper function
size_t next_power_of_two(size_t n)
{
    if (n == 0) return 1;

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

#if SIZE_MAX > 0xFFFFFFFF
    n |= n >> 32;  // for 64-bit 
#endif

    return n + 1;
}


//Function to create a new hashtable
hashtable *create_hashtable(size_t size)
{
    if (size <= 0) return NULL; // Invalid size

    size = next_power_of_two(size); // Ensure size is a power of two

    hashtable *ht = malloc(sizeof(hashtable));
    if(!ht) return NULL;

    ht->bucket = malloc(size * sizeof(struct hashnode*));
    if(!ht->bucket)
    {
        free(ht);
        return NULL; // Memory allocation failed
    }
    ht->size = size;
    ht->cnt = 0;

    return ht;
}


//Hash function djb2
unsigned long hash(char *key)
{
    unsigned long hash = 5381;
    int character;

    while((character = *key++))
    {
        hash = ((hash << 5) + hash) + character; // hash * 33 + c
    }

    return hash;

}

//Helper function to find the load factor of the hashtable
double load_factor(struct hashtable *ht)
{
    if (!ht || ht->size == 0) return 0; // Avoid division by zero
    return (double)ht->cnt / ht->size;
}

//Function to resize the hashtable when the load factor exceeds LOAD_FACTOR
void resize_hashtable(struct hashtable *ht)
{
    if (!ht) return; // Check for null pointer

    int new_size = ht->size * 2;
    struct hashnode **new_bucket = malloc(new_size * sizeof(struct hashnode*));
    if (!new_bucket) return; // Memory allocation failed

    for (int i = 0; i < new_size; i++)
        new_bucket[i] = NULL;

    for (int i = 0; i < ht->size; i++)
    {
        struct hashnode *node = ht->bucket[i];
        while (node)
        {
            struct hashnode *next_node = node->next;
            unsigned long new_index = hash(node->key) &  (new_size-1);

            node->next = new_bucket[new_index];
            new_bucket[new_index] = node; // Rehashing the node to the new bucket

            node = next_node; // Move to the next node in the chain
        }
    }

    free(ht->bucket);
    ht->bucket = new_bucket;
    ht->size = new_size;
}

//Function to insert a key-value pair into the hashtable
void insert_hash(char *key,int value,struct hashtable *ht)
{
    if(!ht || !key) return; 

    if(load_factor(ht) >= LOAD_FACTOR) resize_hashtable(ht);

    unsigned long index = hash(key) & (ht->size - 1);
    
    hashnode *node = ht->bucket[index];

    while(node)
    {
        if(!strcmp(node->key,key))
        {
            node->value = value;
            return; // Key already exists, update value
        }
        node = node->next;
    }

    hashnode *new = malloc(sizeof(hashnode));
    if(!new) return; // Memory allocation failed

    new->key = strdup(key);
    if(!new->key)
    {
        free(new);
        return;
    }
    new->value = value;
    new->next =ht->bucket[index];
    ht->bucket[index] = new;

   ht->cnt++;
}

//Function to search for a value by key in the hashtable
hashnode *search_hash(char *key, hashtable *ht)
{
    if (!ht || !key) return NULL; // Check for null pointers

    unsigned long index = hash(key) & (ht->size-1);
    hashnode *node = ht->bucket[index];

    while (node)
    {
        if (!strcmp(node->key, key))
        {
            return node; // Key found, return the node
        }
        node = node->next; // Move to the next node in the chain
    }

    return NULL; // Key not found
}

//Function to delete a key-value pair from the hashtable
bool delete_hash(char *key, hashtable *ht)
{
    if(!ht || !key) return false;

    unsigned long index = hash(key) & (ht->size-1);
    hashnode *node = ht->bucket[index];
    hashnode *prev = NULL;

    while(node)
    {
        if(!strcmp(node->key,key))
        {
            if(!prev) ht->bucket[index] = node->next;
            else prev->next = node->next;

            free(node->key);
            free(node);
            ht->cnt--;
            return true;
        }
        prev = node;
        node = node->next;
    }

    return false;
}

//Function to free the hashtable
void free_hashtable(hashtable *ht)
{
    if(!ht) return;

    for(int i = 0;i<ht->size;i++)
    {
        hashnode *node = ht->bucket[i];
        while(node)
        {
            hashnode *next_node = node->next;
            free(node->key);
            free(node);
            node = next_node;
        }
    }
    free(ht->bucket);
    free(ht);      
}

//Helper functions

int get_size(hashtable *ht)
{
    if(!ht) return -1; // Check for null pointer
    return ht->size;
}


int get_value(char *key, hashtable *ht)
{
    if(!ht || !key) return -1; // Check for null pointers

    hashnode *node = search_hash(key, ht);
    if(node) return node->value;

    return -1; // Key not found
}