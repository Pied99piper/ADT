#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t bst_t;

bst_t *insert(bst_t *t, int v)
{
    bst_t *pos = t;
    bst_t *new_node,*parent;
    parent = NULL;
    new_node = (bst_t*)malloc(sizeof(bst_t));
    new_node->data = v;
    new_node->left = NULL;
    new_node->right = NULL;
    if (t == NULL){
        return new_node;
    }
    else
        while (pos != NULL){
            parent = pos;
            if (v > pos->data){
                pos = pos->right;
            }
            else
                pos = pos->left;
        }
        if (v > parent->data){
            parent->right = new_node;
        }
        else
            parent->left = new_node;
        return t;
}

int find_min(bst_t *t)
{
    bst_t *pos = t;
    if (t->left == NULL){
        return t->data;
    }
    else
        while (pos->left != NULL){
            pos = pos->left;
        }
        return pos->data;
}

bst_t *delete(bst_t *t, int v)
{
    if (t == NULL){
        return NULL;
    }
    if (v < t->data){
        t->left = delete(t->left,v);
    }
    else if (v > t->data){
        t->right = delete(t->right,v);
    }

    else {
        if (t->left == NULL && t->right == NULL){
            free(t);
            return NULL;
        }
        else if (t->left == NULL){
            bst_t *pos = t->right;
            free(t);
            return pos;
        }
        else if (t->right == NULL){
            bst_t *pos = t->left;
            free(t);
            return pos;
        }
        t->data = find_min(t->right);
        t->right = delete(t->right,find_min(t->right));
    }
    return t;
}

int find(bst_t *t, int v)
{
    if (t != NULL){
        if (t->data == v){
            return 1;
        }
        if (v > t->data){
            return find(t->right,v);
        }
        else
            return find(t->left,v);
    }
    else
        return 0;
}

int find_max(bst_t *t)
{
    bst_t *pos = t;
    if (t->right == NULL){
        return t->data;
    }
    else
        while (pos->right != NULL){
            pos = pos->right;
        }
        return pos->data;
}

int main(void) {
    bst_t *t = NULL;
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
                scanf("%d", &data);
                printf("%d\n", find(t, data));
                break;
            case 4:
                printf("%d\n", find_min(t));
                break;
            case 5:
                printf("%d\n", find_max(t));
                break;
        }
    }
    return 0;
}
