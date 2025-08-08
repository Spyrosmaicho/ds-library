#ifndef HASHTABLE_H
#define HASHTABLE_H

#define LOAD_FACTOR 0.75

typedef struct hashnode hashnode;
typedef struct hashtable hashtable;

#include <stdbool.h>

//Helper function to find the load factor of the hashtable
double load_factor(struct hashtable *ht);

//Function to create a new hashtable
hashtable *create_hashtable(size_t size);

//Function to insert a key-value pair into the hashtable
void insert_hash(char *key,int value,struct hashtable *ht);

//Function to search for a value by key in the hashtable
hashnode *search_hash(char *key, hashtable *ht);

//Function to delete a key-value pair from the hashtable
bool delete_hash(char *key, hashtable *ht);

//Function to free the hashtable
void free_hashtable(hashtable *ht);


//Helper functions

int get_size(hashtable *ht);
int get_value(char *key, hashtable *ht);
size_t next_power_of_two(size_t n);

#endif 