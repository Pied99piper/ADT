#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    int data;
    int mem_addr;
} cell_t;

typedef struct hash {
    cell_t *table;
    int cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int memory_t;

memory_t *init_memory(int size) {
    memory_t *memory = (memory_t *)malloc(
    sizeof(memory_t)*size);
    int i = 0;
    
    for (i=0; i<size; i++)
        memory[i] = rand();
    return memory;
}

cache_t	*init_cache(int size)
{
	cache_t	*cache;
	cache = (cache_t *)malloc(sizeof(cache_t));
	if (!cache)
		return (NULL);
	cache->table = (cell_t *)calloc(sizeof(cell_t), size);
	if (!cache->table)
		return (NULL);
	cache->cache_size = size;
	return (cache);
}

void	get_data(int addr, memory_t *memory, cache_t *cache)
{
	unsigned int cache_index;
	cell_t *cell;
	cache_index = addr % cache->cache_size;
	cell = &cache->table[cache_index];
	if (cell->data != memory[addr]) {
		if (cell->data)
			printf("Index: %u is used\n", cache_index);
		printf("Load from memory\n");
	}
	else
		printf("Address %d is loaded\n", addr);
	cell->data = memory[addr];
	cell->mem_addr = addr;
	printf("Data: %d\n", cell->data);
}

int main(void) {
    memory_t *memory = NULL;
    cache_t *cache = NULL;
    int memory_size, cache_size;
    int i, n, addr;
    scanf("%d %d %d", &memory_size,
    &cache_size, &n);
    memory = init_memory(memory_size);
    cache = init_cache(cache_size);
    for (i=0; i<n; i++) {
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }
    return 0;
}