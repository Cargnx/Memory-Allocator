#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define POOL_SIZE 1024
#define MAX_BLOCKS 32

typedef struct
{
    size_t size;
    bool is_free;
    void *data;
} Block;

typedef struct
{
    size_t used_memory;
    int num_blocks;
    unsigned char memory[POOL_SIZE];
    Block blocks[MAX_BLOCKS];
} MemoryPool;

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

int main()
{
    printf("=== MEMORY ALLOCATOR === \n");
    MemoryPool pool;

    pool_init(&pool);

    int *nums = (int *)pool_alloc(&pool, sizeof(int) * 5);
    if (nums != NULL)
    {
        for (int i = 0; i < 5; ++i)
        {
            nums[i] = i * 10;
        }

        printf("Stored numbers: ");
        for (int i = 0; i < 5; ++i)
        {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }

    return 0;
}