#include <stdlib.h>
#include "bst.h"
#include <string.h>

struct BST
{
    void *val;
    int element_size;
    struct BST *right;
    struct BST *left;
};

/*Function to initialize BST*/
BST *init_bst(int element_size)
{
    BST *bst = malloc(sizeof(BST));
    if(!bst) return NULL;
    bst->element_size = element_size;
    bst->val = NULL;
    bst->left = bst->right = NULL; // Initialize left and right children to NULL
    return bst;
}

/*Function to insert a value into the bst*/
void bst_insert(BST *bst,void *value,Compare cmp)
{
    if(!bst || !value) return;
    if(!bst->val)
    {
        bst->val = malloc(bst->element_size);
        if(!bst->val) return; // If memory allocation fails, do nothing
        memcpy(bst->val, value, bst->element_size); // Copy the value into the bst
        return;
    }
    
    int res = cmp(value,bst->val);
    if(res<0)
    {
        if(!bst->left) bst->left = init_bst(bst->element_size); // Create left child if it doesn't exist
        bst_insert(bst->left, value,cmp); // Insert into left subtree
    }
    else
    {
        if(!bst->right) bst->right = init_bst(bst->element_size); // Create right child if it doesn't exist
        bst_insert(bst->right, value,cmp); // Insert into right subtree
    }

}

/*Function to search for a value in the bst*/
bool bst_search(BST *bst,void *value,Compare cmp)
{
    if(!bst || !value) return false; // If bst or value is NULL, return false
    if(!bst->val) return false; // If bst is empty, return false

    int res = cmp(value, bst->val);
    if(!res) return true;
    else if(res<0)
    {
        if(bst->left) return bst_search(bst->left,value,cmp);
        else return false;
    }
    else
    {
        if(bst->right) return bst_search(bst->right,value,cmp);
        else return false;
    }
}

/*Function to delete a node from bst*/
bool delete_bst(BST **bst,void *value,Compare cmp)
{
    if(!bst || !(*bst) || !value) return false;

    if(!(*bst)->val) return false; // If bst is empty, do nothing

    int res = cmp(value,(*bst)->val);
    if(!res)
    {
        if(!(*bst)->left)
        {
            BST *temp = (*bst)->right;
            free((*bst)->val);
            free(*bst);
            *bst = temp;
            return true;
        }

        if(!(*bst)->right)
        {
            BST *temp = (*bst)->left;
            free((*bst)->val);
            free(*bst);
            *bst = temp;
            return true;
        }

        BST *suc = (*bst)->right;
        while(suc && suc->left) suc = suc->left;

        memcpy((*bst)->val,suc->val,(*bst)->element_size);

        return delete_bst(&(*bst)->right,suc->val,cmp);
    }
    else if(res<0) return delete_bst(&(*bst)->left,value,cmp);  
    return delete_bst(&(*bst)->right,value,cmp); 
}

/*Function to free the bst*/
void free_bst(BST *bst)
{
    if(!bst) return;

    free(bst->val);
    if(bst->left) free_bst(bst->left);
    if(bst->right) free_bst(bst->right);
    free(bst); // Free the BST node itself
}

//Helper function to return bst->val
void *bst_val(BST *bst)
{
    if(!bst) return NULL;
    return bst->val;
}

//Helper funstion to return bst->left
BST *bst_left(BST *bst)
{
    if(!bst) return NULL;
    return bst->left;
}

//Helper funstion to return bst->right
BST *bst_right(BST *bst)
{
    if(!bst) return NULL;
    return bst->right;
}

//Helper function to return bst->element_size
int bst_element_size(BST *bst)
{
    if(!bst) return -1;
    return bst->element_size;
}