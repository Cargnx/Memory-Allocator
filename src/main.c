#include <stdio.h>
#include "memory_pool.h"

int main()
{
    printf("=== MEMORY ALLOCATOR ===\n\n");
    MemoryPool pool;

    pool_init(&pool);

    pool_stats(&pool);

    int *nums = (int *)pool_alloc(&pool, sizeof(int) * 50);
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

    int *nums2 = (int *)pool_alloc(&pool, sizeof(int) * 50);
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

    printf("FREEING...\n\n");
    pool_free(&pool, nums);

    pool_stats(&pool);

    int *nums3 = (int *)pool_alloc(&pool, sizeof(int) * 50);
    if (nums3 != NULL)
    {
        for (int i = 0; i < 5; ++i)
        {
            nums3[i] = i * 10;
        }

        printf("Stored numbers: ");
        for (int i = 0; i < 5; ++i)
        {
            printf("%d ", nums3[i]);
        }
        printf("\n\n");
    }

    pool_stats(&pool);
    pool_free(&pool, nums2);
    pool_free(&pool, nums3);

    printf("=== NEW ALLOCATION ===\n\n");

    pool_init(&pool);

    int *nums4 = (int *)pool_alloc(&pool, sizeof(int) * 30);
    if (nums4 != NULL)
    {
        for (int i = 0; i < 5; ++i)
        {
            nums4[i] = i * 10;
        }

        printf("Stored numbers: ");
        for (int i = 0; i < 5; ++i)
        {
            printf("%d ", nums4[i]);
        }
        printf("\n\n");
    }

    pool_stats(&pool);

    printf("FREEING...\n");
    pool_free(&pool, nums4);

    pool_stats(&pool);

    return 0;
}