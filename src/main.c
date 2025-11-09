#include <stdio.h>
#include "memory_pool.h"

// Helper: Allocates array of integers 
int *alloc_ints(MemoryPool *pool, int count)
{
    return (int *)pool_alloc(pool, sizeof(int) * count);
}

// Fill array with test data and print it
void fill_and_print(int *array, int count)
{
    if (array == NULL)
        return;

    for (int i = 0; i < count; ++i)
        array[i] = i * 10;

    printf("Stored numbers: ");
    for (int i = 0; i < count; ++i)
        printf("%d ", array[i]);
    printf("\n\n");
}

int main()
{
    printf("=== MEMORY ALLOCATOR ===\n\n");
    MemoryPool pool;

    // Initialize pool
    pool_init(&pool);
    pool_stats(&pool);

    // Test 1: Allocate first block
    int *nums1 = alloc_ints(&pool, 50);
    fill_and_print(nums1, 50);
    pool_stats(&pool);

    // Test 2: Allocate second block
    int *nums2 = alloc_ints(&pool, 50);
    fill_and_print(nums2, 50);
    pool_stats(&pool);

    // Test 3: Free first block
    printf("FREEING nums1...\n\n");
    pool_free(&pool, nums1);
    pool_stats(&pool);

    // Test 4: Allocate third block (should reuse freed block)
    int *nums3 = alloc_ints(&pool, 50);
    fill_and_print(nums3, 50);
    pool_stats(&pool);

    // Test 5: Free remaining blocks
    printf("FREEING nums2 and nums3...\n\n");
    pool_free(&pool, nums2);
    pool_free(&pool, nums3);
    pool_stats(&pool);

    // Test 6: Fresh start with new pool
    printf("=== NEW ALLOCATION ===\n\n");
    pool_init(&pool);

    int *nums4 = alloc_ints(&pool, 30);
    fill_and_print(nums4, 30);
    pool_stats(&pool);

    // Cleanup
    printf("FREEING nums4...\n\n");
    pool_free(&pool, nums4);
    pool_stats(&pool);

    return 0;
}