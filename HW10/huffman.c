#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char *data;
    int freq;
    struct node *left, *right;
} node_t ;

typedef struct min_heap {
    int last_index;
    int size;
    node_t **array;
} heap_t ;

heap_t *init_heap(int n)
{
    heap_t *node = (heap_t*)malloc(sizeof(heap_t));
    node->last_index = -1;
    node->size = n;
    node->array = (node_t**)malloc(sizeof(node_t*)*n);
    return node;
}

node_t *build_node(char *arr,int n)
{
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->data = arr;
    temp->freq = n;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insert(heap_t *min,node_t *t)
{
    int par,node,next;
    int v = t->freq;
    node_t *temp = NULL;
    min->last_index += 1;
    min->array[min->last_index] = t;
    if (min->last_index != 0){
        par = ((min->last_index)-1)/2;
        node = min->last_index;
        while (v < (min->array[par])->freq){
            if (par == 0){
                temp = min->array[par];
                min->array[par] = t;
                min->array[node] = temp;
                break;
            }
            temp = min->array[par];
            min->array[par] = t;
            min->array[node] = temp;
            next = (par-1)/2;
            node = par;
            par = next;
        }
    }
}

node_t *delete_min(heap_t *min)
{
    node_t *left = NULL;
    node_t *temp = NULL;
    int node = 0;
    left = min->array[0];
    temp = min->array[min->last_index];
    min->last_index -= 1;
    min->array[0] = temp;
    while (node*2 + 1 < min->last_index || node*2 + 2 < min->last_index){
        int l = (node * 2) + 1;
        int r = (node * 2) + 2;
        if (temp->freq > min->array[l]->freq && min->array[l]->freq <= min->array[r]->freq){
            min->array[node] = min->array[l];
            min->array[l] = temp;
            node = l;
        }
        else if (temp->freq > min->array[r]->freq && min->array[r]->freq < min->array[l]->freq){
            min->array[node] = min->array[r];
            min->array[r] = temp;
            node = r;            
        }
        else {
            break;
        }
    }
    free(temp);
    return left;
}

// void buildhuffman(heap_t *min)
// {
//     node_t *n1 = NULL;
//     // node_t *n2 = NULL;
//     n1 = delete_min(min);
//     // n2 = delete_min(min);
//     printf("%d\n", min->last_index);
//     printf("%s\n", min->array[4]->data);
//     // printf("%s\n", n2->data);
//     printf("%d\n", n1->freq);
// }

int main()
{
    heap_t *min = NULL;
    int time,i;
    scanf("%d", &time);
    min = init_heap(time);
    int freq;
    char word[15];
    for (i = 0; i < time ; ++i){
        scanf("%s %d", word,&freq);
        insert(min,build_node(word,freq));
    }
    printf("%s\n", min->array[4]->data);
    // buildhuffman(min);
    return 0;
}