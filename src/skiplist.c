#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/* Hidden structs from user */
struct Item {
    Key key;
    Value value;
};

const Item NULLitem = {INT_MIN, 0};  //Sentinel for minimum boundary
const Item MAXitem = {INT_MAX, 0};   //Sentinel for maximum boundary

struct STnode {
    Item item;
    link* next;  
    int sz;      
};

struct list {
    link head, z;  
    int N;         
    int lgN;       
};

/* Helper functions */
static inline Key key(Item A) { return A.key; }
static inline bool less(Key A, Key B) { return A < B; }
static inline bool eq(Key A, Key B) { return A == B; }

//Creates new node with k levels
link NEW(Item item, int k, link z) 
{
    link x = malloc(sizeof *x);
    assert(x != NULL);
    x->next = malloc(k * sizeof(link));
    assert(x->next != NULL);
    x->item = item;
    x->sz = k;
    for (int i = 0; i < k; i++) x->next[i] = z;  //Initialize all pointers to sentinel
    return x;
}

/* Initialize the skip list */
SkipList* STinit(int max) 
{
    SkipList* list = malloc(sizeof(SkipList));
    assert(list != NULL);
    list->N = 0;
    list->lgN = 0;

    //Create tail sentinel with INT_MAX
    list->z = NEW(MAXitem, max, NULL);
    //Make sentinel point to itself at all levels
    for (int i = 0; i < max; i++) list->z->next[i] = list->z;

    //Create header node with INT_MIN
    list->head = NEW(NULLitem, max, list->z);

    srand(time(NULL));  //Seed for random level generation
    return list;
}

//Generate random level for new nodes
static int randX() 
{
    int i, j, t = rand();
   
    for (i = 1, j = 2; i < lgNmax; i++, j += j)
        if (t > RAND_MAX / j) break;
    return i;
}

//Recursive insertion helper
static void insertR(link t, link x, int k, link z) 
{
    if (k < 0) return;  //Base case, reached bottom level

    //Traverse current level while keys are smaller than new key
    while (t->next[k] != z && key(t->next[k]->item) < key(x->item)) 
        t = t->next[k];

    //Insert at current level if within nodes level range
    if (k < x->sz) 
    {
        x->next[k] = t->next[k];
        t->next[k] = x;
    }

    //Continue insertion at lower level
    insertR(t, x, k - 1, z);
}

/* Insert a new item */
void STinsert(SkipList* list, Key key, Value value) 
{
    //Update existing key if found
    Value* existing = STsearch(list, key);
    if (existing) 
    {
        *existing = value;
        return;
    }

    Item item = {key, value};
    int new_level = randX();  //Determine new node height
    if (new_level > list->lgN) list->lgN = new_level;  //Update max level if needed

    link new_node = NEW(item, new_level, list->z);
    insertR(list->head, new_node, list->lgN - 1, list->z);
    list->N++;  //Increment element count
}

//Recursive search helper
link searchR(link t, Key v, int k, link z) 
{
    if (t == z) return z;  //Key not found
    if (eq(v, key(t->item))) return t;  //Found exact match

    //If next node key is larger, drop down a level
    if (less(v, key(t->next[k]->item))) 
    {
        if (k == 0) return z;  //Can't drop further
        return searchR(t, v, k - 1, z);
    }
    //Otherwise move forward at current level
    return searchR(t->next[k], v, k, z);
}

/* Search for an item */
Value* STsearch(SkipList* list, Key v) 
{
    link x = searchR(list->head, v, list->lgN, list->z);
    return (x == list->z) ? NULL : &(x->item.value);
}

/* Delete an item */
bool deleteR(link t, Key v, int k, link z) 
{
    if (k < 0) return false;  //no more levels

    link x = t->next[k];
    if (x == z) return deleteR(t, v, k - 1, z);  //End of list, drop level

    if (x->item.key >= v) 
    {
        if (x->item.key == v) 
        {
            //Found node to delete at this level
            t->next[k] = x->next[k];  //Bypass node
            
            if (k == 0) 
            {
                //at bottom level, safe to free memory
                free(x->next);
                free(x);
                return true;
            } 
            else  return deleteR(t, v, k - 1, z); //Continue deletion at lower levels
        } 
        else return deleteR(t, v, k - 1, z); //Node is larger, drop level
    }
    //Node is smaller, move forward at same level
    return deleteR(x, v, k, z);
}

/*Merge two lists using cookbook algorithm*/
SkipList* STmerge(SkipList* list1, SkipList* list2) 
{
    if (!list1) return list2;
    if (!list2) return list1;

    //Determine new list max level
    int max_level = (list1->lgN > list2->lgN) ? list1->lgN : list2->lgN;
    SkipList* list = malloc(sizeof(SkipList));
    if (!list) return NULL;

    list->N = 0;
    list->lgN = max_level;

    /* Create new sentinel and header for merged list */
    //Sentinel node (z) setup
    list->z = malloc(sizeof(struct STnode));
    if (!list->z) 
    {
         free(list);
        return NULL;
    }
    list->z->item.key = INT_MAX;
    list->z->sz = max_level;
    list->z->next = malloc(max_level * sizeof(struct STnode*));
    if (!list->z->next) free(list->z);
    for (int i = 0; i < max_level; i++) list->z->next[i] = list->z;

    //Header node setup
    list->head = malloc(sizeof(struct STnode));
    if (!list->head) free(list->z->next);
    list->head->item.key = -1;
    list->head->sz = max_level;
    list->head->next = malloc(max_level * sizeof(struct STnode*));
    if (!list->head->next) free(list->head);
    for (int i = 0; i < max_level; i++) list->head->next[i] = list->z;

    //Update array for maintaining last pointers per level
    struct STnode** update = malloc(max_level * sizeof(struct STnode*));
    if (!update) free(list->head->next);
    for (int i = 0; i < max_level; i++) update[i] = list->head;

    /*Merge algorithm: Cookbook method */
    struct STnode* x = list1->head->next[0];
    struct STnode* y = list2->head->next[0];
    int duplicates = 0;

    //Process nodes while both lists have elements
    while (x != list1->z && y != list2->z) 
    {
        //Choose smaller key (x or y)
        struct STnode** target = (x->item.key <= y->item.key) ? &x : &y;
        int level = (*target)->sz;
        
        //Connect to update pointers at all levels
        for (int i = 0; i < level; i++) 
        {
            update[i]->next[i] = *target;
            update[i] = *target;  //Move update pointer forward
        }
        
        //Handle duplicate keys
        if (x->item.key == y->item.key) 
        {
            // Update value from second list
            x->item.value = y->item.value;
            duplicates++;
            
            struct STnode* temp = y;
            y = y->next[0];
            
            //Remove node from list2 by fixing its pointers
            for (int i = 0; i < temp->sz; i++)
             {
                if (list2->head->next[i] == temp) list2->head->next[i] = temp->next[i];
            }
            
            //Maintain list2's element count
            list2->N--;
            
            free(temp->next);
            free(temp);
        }
        
        //Move to next node in selected list
        *target = (*target)->next[0];
    }
    
    /* Append remaining elements */
    struct STnode* remaining = (x != list1->z) ? x : y;
    while (remaining != list1->z && remaining != list2->z) 
    {
        int level = remaining->sz;
        for (int i = 0; i < level; i++) 
        {
            update[i]->next[i] = remaining;
            update[i] = remaining;
        }
        remaining = remaining->next[0];
    }
    
    //Terminate all levels with sentinel
    for (int i = 0; i < max_level; i++) update[i]->next[i] = list->z;
    
    
    //Calculate size accounting for duplicates removed during merge
    list->N = list1->N + list2->N;
    
    //Disable original lists (without destroying nodes)
    for (int i = 0; i < list1->lgN; i++) list1->head->next[i] = list1->z;
    for (int i = 0; i < list2->lgN; i++) list2->head->next[i] = list2->z;
    list1->N = list2->N = 0;
    
    //Reduce max level if top levels are empty
    while (list->lgN > 1 && list->head->next[list->lgN - 1] == list->z)
        list->lgN--;
    
    free(update);
    return list;

}

/* Delete an item */
bool STdelete(SkipList* list, Key v) 
{
    bool deleted = deleteR(list->head, v, list->lgN, list->z);
    if (deleted) 
    {
        list->N--;  //Decrement element count
        
        //Reduce max level if top levels become empty
        while (list->lgN > 1 && list->head->next[list->lgN - 1] == list->z)
            list->lgN--;
    }
    return deleted;
}

/*Utility Functions*/
void STprint(SkipList* list) 
{
    if (list->head->next[0] == list->z) 
    {
        printf("NULL\n");
        return;
    }
    
    //Print from top level to bottom
    for (int i = list->lgN - 1; i >= 0; i--) 
    {
        printf("Level %d: ", i);
        link node = list->head->next[i];
        while (node != list->z) 
        {
            printf("%d(%d) ", node->item.key, node->item.value);
            node = node->next[i];
        }
        printf("\n");
    }
}

int STcount(SkipList* list) 
{
    return list->N;
}

void STdestroy(SkipList* list) 
{
    //Destroy all nodes
    link current = list->head->next[0];
    while (current != list->z) 
    {
        link next = current->next[0];
        free(current->next);
        free(current);
        current = next;
    }
    
    //Destroy infrastructure
    free(list->head->next);
    free(list->head);
    free(list->z->next);
    free(list->z);
    free(list);
}