#include "avl.h"
#include <stdlib.h>

/*Hidden struct from user*/
struct avl
{
    int key;
    int height;
    struct avl *right;
    struct avl *left;
};

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//Function that returns the height of a node in avl
int get_height(avl *node)
{
    if(!node) return 0;
    return node->height;
}

//Helper functions for rotations

//right rotation function
avl *right_rotation(avl *node)
{
    if (!node || !node->left) return node; 

    avl *l = node->left;
    avl *r = l->right;

    l->right = node;
    node->left = r;
    
    node->height = 1 + MAX(get_height(node->left),get_height(node->right));

    l->height = 1 + MAX(get_height(l->left),get_height(l->right));

    return l;
}

//left rotation function
avl *left_rotation(avl *node)
{
    if (!node || !node->right) return node; 

    avl *r = node->right;
    avl *l = r->left;

    r->left = node;
    node->right = l;
    
    node->height = 1 + MAX(get_height(node->left),get_height(node->right));

    r->height = 1 + MAX(get_height(r->left),get_height(r->right));

    return r;
}

//Function that searches a specific value in the avl tree
avl *search_avl(avl *root,int val)
{
    if(!root || root->key == val ) return root;

    if(val < root->key) return search_avl(root->left,val);

    return search_avl(root->right,val);
}

//Function to get the balance factor of a node in avl
int balance_factor(avl *node)
{
    if(!node) return 0;

    return get_height(node->left) - get_height(node->right);
}

//Create a node in the avl tree
avl *create_avl(int value)
{
    avl *node = malloc(sizeof(avl));
    if(!node) return NULL;
    node->left = node->right = NULL;
    node->height = 1;
    node->key = value;
    return node;
}

//Insert a node in the avl tree
avl *insert_avl(avl *root,int value)
{
    if(!root) 
    {
        
        avl *node =  create_avl(value);
        if(!node) return NULL;
        return node;
    }

    if(root->key > value)  root->left = insert_avl(root->left,value);
     else if (value > root->key)   root->right = insert_avl(root->right, value);
    else // Equal keys are not allowed in BST
        return root;

    //Update the height
    root->height = 1 + MAX(get_height(root->left), get_height(root->right));

    int balance = balance_factor(root);

    if(balance > 1 && value < root->left->key) return right_rotation(root); //right-right

    if(balance < -1 && value > root->right->key) return left_rotation(root); //left-left

    if(balance > 1 && value > root->left->key) 
    {
        root->left = left_rotation(root->left); //left-right
        root =  right_rotation(root);
    }

    if(balance < -1 && value < root->right->key) //right-left
    {
        root->right = right_rotation(root->right);
        root = left_rotation(root);
    }

    return root;
}

//Helper function to find the in-order successor
avl *find_succ(avl *node)
{
    if(!node) return NULL;
    
    while(node->left) node = node->left;

    return node;
}

//Function to delete a node from the avl tree
avl *delete_avl(avl *root,int value)
{
    if(!root) return NULL;

    if(value < root->key) root->left =  delete_avl(root->left,value);
    else if(value > root->key) root->right = delete_avl(root->right,value);
    else //we found the value
    {
        // Node with only one child or no child
        if (!root->left || !root->right)
        {
            avl *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else
        {
            avl *succ = find_succ(root->right);
            root->key = succ->key;
            root->right = delete_avl(root->right,succ->key);
        }
    }

    //Update height
    root->height = 1 + MAX(get_height(root->left),get_height(root->right));

    int balance = balance_factor(root);

    //Check and fix imbalance 
    if(balance > 1 && value < root->left->key) return right_rotation(root);

    if(balance < -1 && value > root->right->key) return left_rotation(root);

    if(balance > 1 && value > root->left->key) 
    {
        root->left = left_rotation(root->left);
        return right_rotation(root);
    }

    if(balance < -1 && value < root->right->key)
    {
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }

    return root;
}

//Helper functions to return the key of a node
int get_key(avl *node)
{
    return node->key;
}

int get_left_key(avl *node)
{
    return node->left->key;
}

int get_right_key(avl *node)
{
    return node->right->key;
}

//Function to destroy all memory allocated for avl tree
void destroy_avl(avl *root)
{
    if(!root) return;

    if(root->right) destroy_avl(root->right);
    if(root->left) destroy_avl(root->left);
    free(root);
}