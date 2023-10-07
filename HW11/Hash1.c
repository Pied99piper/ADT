#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef struct item {
    char *text;
    struct item *next;
} item_t;

typedef struct hash {
    item_t **table;
    int size;
    int hash_key;
} hash_t;

hash_t *init_hashtable(int m, int hash_key)
{
    hash_t *hashtable = (hash_t*)malloc(sizeof(hash_t));
    hashtable->hash_key = hash_key;
    hashtable->size = m;
    hashtable->table = calloc(m, sizeof(item_t*));
    return hashtable;
}

item_t *createNode(char *text)
{
    item_t *temp = (item_t*)malloc(sizeof(item_t*));
    temp->text = (char*)malloc(sizeof(char)*strlen(text));
    strcpy(temp->text,text);
    temp->next = NULL;
    return temp;
}

unsigned int pre(char *text, int key)
{
    int i;
    unsigned int hash = 0;
    for (i = 0 ; i < strlen(text) ; ++i){
        hash = (hash * key) + text[i];
    }
    return hash;
}

unsigned int positon(unsigned int hash,int size)
{
    return (hash % size);
}

void insert(hash_t *hash,char *text)
{
    unsigned int map = positon(pre(text,hash->hash_key),hash->size);
    item_t *node = createNode(text);
    if (hash->table[map] != NULL){
        node->next = hash->table[map];
    }
    hash->table[map] = node;
}

int search(hash_t *hash,char *text)
{
    unsigned int map = positon(pre(text,hash->hash_key),hash->size);
    if (hash->table[map] != NULL){
        item_t *pos = hash->table[map];
        while (pos != NULL){
            if (!strcmp(pos->text,text)){
                return map;
            }
            pos = pos->next;
        }
    }
    return (-1);
}

int main(void) {
    hash_t *hashtable = NULL;
    char *text = NULL;
    int m, n, i, hash_key;
    int command;
    scanf("%d %d %d", &m, &n, &hash_key);
    hashtable = init_hashtable(m, hash_key);
    text = (char *)malloc(sizeof(char)*TEXTSIZE);
    for (i=0; i<n; i++) {
        scanf("%d %s", &command, text);
        switch (command) {
            case 1:
                insert(hashtable, text);
                break;
            case 2:
                printf("%d\n",search(hashtable, text));
                break;
        }
    }
    return 0;
}