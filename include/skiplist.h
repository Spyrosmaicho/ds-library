#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <stdbool.h>
#include <limits.h>

#define lgNmax 16  //Maximum level

typedef int Key;
typedef int Value;
typedef struct STnode* link;
typedef struct Item Item;
typedef struct list SkipList;

extern const Item NULLitem;

/* Initialize the skip list */
SkipList *STinit(int max);  

/* Return number of elements */
int STcount(SkipList *list);       

/* Insert a new item */
void STinsert(SkipList *list, Key key, Value value);

/* Search for an item */
Value* STsearch(SkipList *list, Key key); 

/* Delete an item */
bool STdelete(SkipList *list, Key key);  

/*Merge two lists using cookbook algorithm*/
SkipList *STmerge(SkipList *list1, SkipList *list2);

/* Print the skip list */
void STprint(SkipList *list);            

/* Destroy the skip list */
void STdestroy(SkipList *list);          



#endif