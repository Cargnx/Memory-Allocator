#include "memory_pool.h"
#include <stdio.h>
#include <string.h>

void pool_init(MemoryPool *pool)
{
    memset(pool->blocks, 0, sizeof(Block) * MAX_BLOCKS);
    memset(pool->memory, 0, POOL_SIZE);
    pool->used_memory = 0;
    pool->num_blocks = 0;
    printf("Memory pool initialized with %d bytes\n", POOL_SIZE);
}

void *pool_alloc(MemoryPool *pool, size_t size)
{
    if (size == 0 || size > POOL_SIZE)
    {
        fprintf(stderr, "Invalid allocation size!\n");
        return NULL;
    }

    if (pool->used_memory + size > POOL_SIZE)
    {
        fprintf(stderr, "Not enough Memory!\n");
        return NULL;
    }

    if (pool->num_blocks >= MAX_BLOCKS)
    {
        fprintf(stderr, "Exceeding Max Block size!\n");
        return NULL;
    }

    void *ptr = &pool->memory[pool->used_memory];

    Block *block = &pool->blocks[pool->num_blocks];

    block->size = size;
    block->is_free = false;
    block->data = ptr;

    pool->num_blocks++;
    pool->used_memory += size;

    printf("Allocated %zu bytes\n", size);

    return ptr;
}

void pool_free(MemoryPool *pool, void *ptr)
{
    if (ptr == NULL)
    {
        printf("Nothing to free...\n");
        return;
    }

    for (int i = 0; i < pool->num_blocks; ++i)
    {
        if (pool->blocks[i].data == ptr && pool->blocks[i].is_free == false)
        {
            pool->blocks[i].is_free = true;
            pool->used_memory -= pool->blocks[i].size;

            printf("Freed %zu Bytes!\n\n", pool->blocks[i].size);
            return;
        }
    }

    fprintf(stderr, "Warning: Attempted to free invalid pointer!\n\n");
}