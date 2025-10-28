#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 1024
#define MAX_BLOCKS 32

typedef struct
{
    size_t size;
    bool is_free;
    void *data;
    void TEST;
} Block;

typedef struct
{
    size_t used_memory;
    int num_blocks;
    unsigned char memory[POOL_SIZE];
    Block blocks[MAX_BLOCKS];
} MemoryPool;

void pool_init(MemoryPool *pool);
void *pool_alloc(MemoryPool *pool, size_t size);
void pool_free(MemoryPool *pool, void *ptr);

#endif