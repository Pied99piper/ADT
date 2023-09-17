#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

#ifndef __avl_tree__
typedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t avl_t;
#endif

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

avl_t *newnode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data   = data;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}

avl_t *find_min(avl_t *t)
{
    avl_t *pos = t;
    while (pos->left != NULL){
        pos = pos->left;
    }
    return pos;
}

avl_t *rightrotate(struct node *pos)
{
    struct node *x = pos->left;
    struct node *T2 = x->right;
    x->right = pos;
    pos->left = T2;
    pos->height = max(height(pos->left),height(pos->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    return x;
}

avl_t *leftrotate(struct node *per)
{
    struct node *pos = per->right;
    struct node *T2 = pos->left;
    pos->left = per;
    per->right = T2;
    per->height = max(height(per->left),height(per->right)) + 1;
    pos->height = max(height(pos->left),height(pos->right)) + 1;
    return pos;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

avl_t *insert(struct node* node, int data)
{
    if (node == NULL)
        return (newnode(data));
 
    if (data < node->data)
        node->left  = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;
 
    node->height = 1 + max(height(node->left),height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightrotate(node);
    if (balance < -1 && data > node->right->data)
        return leftrotate(node);
    if (balance > 1 && data > node->left->data)
    {
        node->left =  leftrotate(node->left);
        return rightrotate(node);
    }
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }
    return node;
}

avl_t* delete(avl_t* root, int data)
{
    if (root == NULL)
        return root;
    if ( data < root->data )
        root->left = delete(root->left, data);
    else if( data > root->data )
        root->right = delete(root->right, data);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            avl_t *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp;
            free(temp);
        }
        else
        {
            avl_t* temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    if (root == NULL)
      return root;
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightrotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftrotate(root->left);
        return rightrotate(root);
    }if (balance < -1 && getBalance(root->right) <= 0)
        return leftrotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }
    return root;
}

int main(void) {
    avl_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 3:
                print_tree(t);
                break;
        }
    }
    return 0;
}