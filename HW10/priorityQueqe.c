#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
int *data;
int last_index;
} heap_t;

heap_t *init_heap(int m)
{
    heap_t *node = (heap_t*)malloc(sizeof(heap_t));
    node->last_index = -1;
    node->data = (int*)malloc(sizeof(int)*m);
    return node;
}

void insert(heap_t *max,int v)
{
    int par,temp,node,next;
    max->last_index += 1;
    max->data[max->last_index] = v;
    if (max->last_index != 0){
        par = (max->last_index-1)/2;
        node = max->last_index;
        while (v > max->data[par]){
            if (par == 0){
                temp = max->data[par];
                max->data[par] = v;
                max->data[node] = temp;
                break;
            }
            temp = max->data[par];
            max->data[par] = v;
            max->data[node] = temp;
            next = (par-1)/2;
            node = par;
            par = next;
        }
    }
}

void delete_max(heap_t *max)
{
    int temp,node = 0;
    if (max->last_index == -1){
        return;
    }
    temp = max->data[max->last_index];
    max->last_index -= 1;
    max->data[0] = temp;
    while (node*2 + 1 < max->last_index || node*2 + 2 < max->last_index){
        int l = (node * 2) + 1;
        int r = (node * 2) + 2;
        if (temp < max->data[l] && max->data[l] > max->data[r]){
            max->data[node] = max->data[l];
            max->data[l] = temp;
            node = l;
        }
        else if (temp < max->data[r] && max->data[r] > max->data[l]){
            max->data[node] = max->data[r];
            max->data[r] = temp;
            node = r;
        }
        else {
            break;
        }
    }
}

void update_key(heap_t *max,int old,int new)
{
    int where = 0,i,par,next,node,temp;
    for (i = 0; i < (max->last_index + 1) ; ++i){
        if (max->data[i] == old){
            where = i;
            break;
        }
    }
    max->data[where] = new;
    if (new > max->data[(where-1)/2]){   
        par = (where-1)/2;
        node = where;
        while (new > max->data[par]){
            if (par == 0){
                temp = max->data[par];
                max->data[par] = new;
                max->data[node] = temp;
                break;
            }
            temp = max->data[par];
            max->data[par] = new;
            max->data[node] = temp;
            next = (par-1)/2;
            node = par;
            par = next;
        }       
    }
    else if (new < max->data[ (where*2 + 1 )] || new < max->data[(where*2 + 2)]){
        temp = new;
        node = where;
        while (node*2 + 1 < max->last_index || node*2 + 2 < max->last_index){
            int l = (node * 2) + 1;
            int r = (node * 2) + 2;
            if (temp < max->data[l] && max->data[l] > max->data[r]){
                max->data[node] = max->data[l];
                max->data[l] = temp;
                node = l;
            }
            else if (temp < max->data[r] && max->data[r] > max->data[l]){
                max->data[node] = max->data[r];
                max->data[r] = temp;
                node = r;
            }
            else {
                break;
            }
        }    
    }
    else{
        return;
    }
}

int find_max(heap_t *max)
{
    if (max->last_index == -1){
        return -1;
    }
    else {
        return max->data[0];
    }
}

void bfs(heap_t *max)
{
    int j = max->last_index,i;
    if (j != -1){
        for (i = 0; i < j + 1 ; ++i){
            printf("%d ",max->data[i]);
        }
    }
    printf("\n");
}

int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                insert(max_heap, data);
                break;
            case 2:
                delete_max(max_heap);
                break;
            case 3:
                printf("%d\n", find_max(max_heap));
                break;
            case 4:
                scanf("%d %d", &old_key, &new_key);
                update_key(max_heap, old_key,new_key);
                break;
            case 5:
                bfs(max_heap);
                break;
        }
    }
    return 0;
}