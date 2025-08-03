#ifndef AVL_H
#define AVL_H

typedef struct avl avl;

//Function that searches a specific value in the avl tree
avl *search_avl(avl *root,int val);

//Insert a node in the avl tree
avl *insert_avl(avl *root,int value);

//Function to delete a node from the avl tree
avl *delete_avl(avl *root,int value);

//Helper functions to return the key of a node
int get_key(avl *node);

int get_left_key(avl *node);

int get_right_key(avl *node);

//Function that returns the height of a node in avl
int get_height(avl *node);

//Function to destroy all memory allocated for avl tree
void destroy_avl(avl *root);

#endif