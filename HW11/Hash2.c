#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef char* item_t;

typedef struct hash {
    item_t *table;
    int size;
    int hash_key;
} hash_t;

hash_t	*init_hashtable(int sizeTable, int hash_key)
{
	hash_t	*hash;
	hash = (hash_t*)malloc(sizeof(hash_t));
	if (!hash)
		return (NULL);
	hash->table = (item_t*)calloc(sizeof(item_t), sizeTable);
	if (!hash->table)
		return (NULL);
	hash->size = sizeTable;
	hash->hash_key = hash_key;
	return (hash);
}

unsigned int sequence(hash_t *hash, char *text)
{
	unsigned int hash_value;
	hash_value = text[0];
	for (int i = 1; i < strlen(text); i++) {
		hash_value = (hash->hash_key * hash_value) + text[i];
    }
	return (hash_value % hash->size);
}

unsigned int level(unsigned int i)
{
	return ((i + i*i) / 2);
}

void insert(hash_t *hashtable, char *text)
{
	item_t	new_item;
	unsigned int hash_index, start, i = 1;
	new_item = strcpy(malloc(strlen(text)), text);
	if (!new_item){
		return;
    }
	start = hash_index = sequence(hashtable, text);
	while ((hashtable->table)[hash_index])
	{
		hash_index = (start + level(i++)) % hashtable->size;
		if (hash_index == start){
			return;
        }
	}
	(hashtable->table)[hash_index] = new_item;
}

int	search(hash_t *hashtable, char *text)
{
	unsigned int hash_index, start, i = 1;
	start = hash_index = sequence(hashtable, text);
	while ((hashtable->table)[hash_index])
	{
		if (strcmp((hashtable->table)[hash_index], text) == 0)
			return (hash_index);
		hash_index = (start + level(i++)) % hashtable->size;
		if (hash_index == start)
			return (-1);
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
                printf("%d\n",
                search(hashtable, text));
                break;
        }
    }
    return 0;
}