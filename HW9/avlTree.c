#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

#ifndef __avl_tree__
tpospedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;
tpospedef node_t avl_t;
#endif

int height(avl_t *N)
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
    avl_t* node = (avl_t*)malloc(sizeof(struct node));
    node->data   = data;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}

avl_t *righrotate(avl_t *pos)
{
    avl_t *x = pos->left;
    avl_t *T2 = x->right;
    x->right = pos;
    pos->left = T2;
    pos->height = max(height(pos->left),height(pos->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    return x;
}

avl_t *leftrotate(avl_t *per)
{
    avl_t *pos = per->right;
    avl_t *T2 = pos->left;
    pos->left = per;
    per->right = T2;
    per->height = max(height(per->left),height(per->right)) + 1;
    pos->height = max(height(pos->left),height(pos->right)) + 1;
    return pos;
}

int getBalance(avl_t *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

avl_t *find_min(avl_t *t)
{
    avl_t *pos = t;
    while (pos->left != NULL){
        pos = pos->left;
    }
    return pos;
}

avl_t *insert(avl_t* node, int data)
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
        return righrotate(node);
    if (balance < -1 && data > node->right->data)
        return leftrotate(node);
    if (balance > 1 && data > node->left->data)
    {
        node->left =  leftrotate(node->left);
        return righrotate(node);
    }
    if (balance < -1 && data < node->right->data)
    {
        node->right = righrotate(node->right);
        return leftrotate(node);
    }
    return node;
}

avl_t *delete(avl_t* t, int data)
{
    if (t == NULL)
        return t;
    if ( data < t->data )
        t->left = delete(t->left, data);
    else if( data > t->data )
        t->right = delete(t->right, data);
    else
    {
        if( (t->left == NULL) || (t->right == NULL) )
        {
            avl_t *temp = t->left ? t->left : t->right;
            if (temp == NULL)
            {
                temp = t;
                t = NULL;
            }
            else 
             *t = *temp;
            free(temp);
        }
        else
        {
            avl_t* temp = find_min(t->right);
            t->data = temp->data;
            t->right = delete(t->right, temp->data);
        }
    }
    if (t == NULL)
      return t;
    t->height = 1 + max(height(t->left),
                           height(t->right));
    int balance = getBalance(t);
    if (balance > 1 && getBalance(t->left) >= 0)
        return righrotate(t);
    if (balance > 1 && getBalance(t->left) < 0)
    {
        t->left =  leftrotate(t->left);
        return righrotate(t);
    }if (balance < -1 && getBalance(t->right) <= 0)
        return leftrotate(t);
    if (balance < -1 && getBalance(t->right) > 0)
    {
        t->right = righrotate(t->right);
        return leftrotate(t);
    }
    return t;
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
