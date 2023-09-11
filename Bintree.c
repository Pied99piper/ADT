#include <stdio.h>
#include <stdlib.h>
#include "week8.h"
#ifndef __bin_tree__
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int cal_height(tree_t *t)
{
    if (t == NULL){
        return 0;
    }
    else {
        int rnode = cal_height(t->right);
        int lnode = cal_height(t->left);
        if (lnode > rnode){
            return (lnode + 1);
        }
        else {
            return (rnode + 1);
        }
    }
}

int count_node(tree_t *t)
{
    if (t == NULL)
        return 0;
    return 1 + (count_node(t->left) + count_node(t->right));
}

int find_nb(tree_t *t)
{
    if (t != NULL){
        if (t->left == NULL && t->right == NULL){
            return t->nb;
        }
        else{
            int lnb = find_nb(t->left);
            int rnb = find_nb(t->right);
            
            return (lnb > rnb)? lnb : rnb;
        }
    }
    return 0;
}

int is_full(tree_t *t)
{
    if (t == NULL){
        return 1;
    }
    if ((t->left == NULL) && (t->right == NULL)){
        return 1;
    }
    if ((t->left) && (t->right)){
        return (is_full(t->left) && is_full(t->right));
    }
    return 0;
}

int is_perfect(tree_t *t)
{
    if (count_node(t->left) == count_node(t->right)){
        return 1;
    }
    else
        return 0;
}

int is_degenerate(tree_t *t)
{
    if (t == NULL){
        return 1;
    }
    if (t->left && t->right){
        return 0;
    }
    return is_degenerate(t->left) * is_degenerate(t->right);
}

int is_complete(tree_t *t)
{
    int node = count_node(t);
    if (t != NULL){
        if (node == find_nb(t)){
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

int is_skewed(tree_t *t)
{
    tree_t *pos = t->left;
    tree_t *temp = t->right;
    int node_left = 0,node_right = 0;
    int node = count_node(t);
    while (pos != NULL){
        node_left++;
        pos = pos->left;
    }
    while (temp != NULL) {
        node_right++;
        temp = temp->right;
    }
    if ((node_left == node - 1) || (node_right == node - 1)){
        return 1;
    }
    else
        return 0;
}

int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child,&branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d %d %d %d %d\n", is_full(t),is_perfect(t), is_complete(t),is_degenerate(t), is_skewed(t));
    return 0;
}