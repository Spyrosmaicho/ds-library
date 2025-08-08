#ifndef HASHTABLE_H
#define HASHTABLE_H

#define LOAD_FACTOR 0.75

typedef struct hashnode hashnode;
typedef struct hashtable hashtable;

#include <stdbool.h>

//Helper function to find the load factor of the hashtable
double load_factor(const struct hashtable *ht);

//Function to create a new hashtable
hashtable *create_hashtable(size_t size);

//Function to insert a key-value pair into the hashtable
void insert_hash(const char *key,int value,struct hashtable *ht);

//Function to search for a value by key in the hashtable
hashnode *search_hash(const char *key,const hashtable *ht);

//Function to delete a key-value pair from the hashtable
bool delete_hash(const char *key, hashtable *ht);

//Function to free the hashtable
void free_hashtable(hashtable *ht);


//Helper functions

int get_size(const hashtable *ht);
hashnode *get_node(const char *key,const hashtable *ht);
//User first call get_node to get the node, then call this function to get the value
int get_value(const hashnode *node);
size_t next_power_of_two(size_t n);

#endif 