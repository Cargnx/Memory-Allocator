#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define POOL_SIZE 1024

typedef struct MemoryPool {
    unsigned char memory[POOL_SIZE];
    size_t used_memory;

} MemoryPool;

void pool_init(MemoryPool* pool) {
    memset(pool->memory, 0, POOL_SIZE);
    pool->used_memory = 0;
    printf("Memory pool initialized with %d bytes\n", POOL_SIZE);
}

void* pool_alloc(MemoryPool* pool, size_t size) {
    if (size == 0 || size > POOL_SIZE) {
        fprintf(stderr, "Invalid allocation size!\n");
        return NULL;
    }

    if (pool->used_memory + size > POOL_SIZE) {
        fprintf(stderr, "Not enough Memory!\n");
        return NULL;
    }

    void* ptr = &pool->memory[pool->used_memory];
    pool->used_memory += size;

    printf("Allocated %zu bytes\n", size);

    return ptr;
}

int main() {
    printf("=== MEMORY ALLOCATOR === \n");
    MemoryPool pool;

    pool_init(&pool);

    int* nums = (int*)pool_alloc(&pool, sizeof(int) * 5);
    if (nums != NULL) {
        for (int i = 0; i < 5; ++i) {
            printf("%d ", nums[i]);
        }
        printf("Stored numbers: ");
        for (int i = 0; i < 5; ++i) {
            printf("%d", nums[i]);
        }
        printf("\n");
    }

    return 0;
}