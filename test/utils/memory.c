#include "dsa/utils/memory.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#define suite utils_memory

#define BUFFER_SIZE 5
#define BUFFER_ELEMS 0, 1, 2, 3, 4

Test(suite, buffer_index)
{
    int arr[BUFFER_SIZE] = {BUFFER_ELEMS};
    int* arr_ptr = arr;
    void* buffer = arr;

    for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++, arr_ptr++) {
        cr_assert(eq(int, arr[i], *(int*)buf_idx(buffer, i, sizeof(int))));
        cr_assert(eq(ptr, arr_ptr, buf_idx(buffer, i, sizeof(int))));
    }
}

Test(suite, buffer_increment)
{
    int arr[BUFFER_SIZE] = {BUFFER_ELEMS};
    int* arr_ptr = arr;
    void* buffer = arr;

    for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++, arr_ptr++) {
        cr_assert(eq(int, arr[i], *(int*)buffer));
        cr_assert(eq(ptr, arr_ptr, buffer));
        buf_inc(buffer, 1, sizeof(int));
    }
}

#undef suite
