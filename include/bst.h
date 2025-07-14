#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct BST BST;

typedef int (*Compare)(const void *a, const void *b);

/*Function to initialize BST*/
BST *init_bst(int element_size);

/*Function to insert a value into the bst*/
void bst_insert(BST *bst,void *value,Compare cmp);

/*Function to search for a value in the bst*/
bool bst_search(BST *bst,void *value,Compare cmp);

/*Function to delete a node from bst*/
bool delete_bst(BST **bst,void *value,Compare cmp);

/*Function to free the bst*/
void free_bst(BST *bst);

//Helper function to return bst->element_size
int bst_element_size(BST *bst);

//Helper funstion to return bst->right
BST *bst_left(BST *bst);

//Helper funstion to return bst->left
BST *bst_right(BST *bst);

//Helper function to return bst->val
void *bst_val(BST *bst);

#endif