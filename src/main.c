#include <stdio.h>
#include "memory_pool.h"

int main()
{
    printf("=== MEMORY ALLOCATOR ===\n\n");
    MemoryPool pool;

    pool_init(&pool);

    pool_stats(&pool);

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
        printf("\n\n");
    }

    pool_stats(&pool);
    printf("FREEING...\n\n");
    pool_free(&pool, nums);

    pool_stats(&pool);

    printf("=== NEW ALLOCATION ===\n\n");

    pool_init(&pool);

    int *nums2 = (int *)pool_alloc(&pool, sizeof(int) * 9);
    if (nums2 != NULL)
    {
        for (int i = 0; i < 5; ++i)
        {
            nums2[i] = i * 10;
        }

        printf("Stored numbers: ");
        for (int i = 0; i < 5; ++i)
        {
            printf("%d ", nums2[i]);
        }
        printf("\n\n");
    }

    pool_stats(&pool);

    printf("FREEING...\n");
    pool_free(&pool, nums2);

    pool_stats(&pool);

    return 0;
}