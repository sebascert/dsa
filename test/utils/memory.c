#include "dsa/utils/memory.h"

#include "dsa/types/array.h"

#include <criterion/criterion.h>
#include <criterion/internal/new_asserts.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

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

Test(suite, swap_return_codes)
{
    char buffer[BUFFER_SIZE] = {BUFFER_ELEMS};
    char memb_buffer;

    struct array valid_arr = {buffer, BUFFER_SIZE, sizeof(char)};
    struct array null_arr = NULL_ARRAY;
    struct array null_buffer_arr = {NULL, BUFFER_SIZE, sizeof(char)};
    struct array zero_size_arr = {buffer, 0, sizeof(char)};
    struct array zero_memb_size_arr = {buffer, BUFFER_SIZE, 0};

    // null fields
    cr_assert(eq(int, 1, swap(&null_arr, 0, 0)));
    cr_assert(eq(int, 1, swap(&null_buffer_arr, 0, 0)));
    cr_assert(eq(int, 1, swap(&zero_size_arr, 0, 0)));
    cr_assert(eq(int, 1, swap(&zero_memb_size_arr, 0, 0)));
    cr_assert(eq(int, 1, swap_with_mbuffer(&null_arr, &memb_buffer, 0, 0)));
    cr_assert(
        eq(int, 1, swap_with_mbuffer(&null_buffer_arr, &memb_buffer, 0, 0)));
    cr_assert(
        eq(int, 1, swap_with_mbuffer(&zero_size_arr, &memb_buffer, 0, 0)));
    cr_assert(
        eq(int, 1, swap_with_mbuffer(&zero_memb_size_arr, &memb_buffer, 0, 0)));
    cr_assert(eq(int, 1, swap_with_mbuffer(&valid_arr, NULL, 0, 0)));

    // out of bounds
    cr_assert(eq(int, 1, swap(&valid_arr, 6, 0)));
    cr_assert(eq(int, 1, swap(&valid_arr, 0, 6)));
    cr_assert(eq(int, 1, swap_with_mbuffer(&valid_arr, &memb_buffer, 6, 0)));
    cr_assert(eq(int, 1, swap_with_mbuffer(&valid_arr, &memb_buffer, 0, 6)));

    // valid
    cr_assert(eq(int, 0, swap(&valid_arr, 0, 0)));
    cr_assert(eq(int, 0, swap_with_mbuffer(&valid_arr, &memb_buffer, 0, 0)));
}

#define SWAP_TESTS(memb_size)                                              \
    TheoryDataPoints(suite, swap_##memb_size##byte_elem_theory) = {        \
        DataPoints(size_t, BUFFER_ELEMS),                                  \
        DataPoints(size_t, BUFFER_ELEMS),                                  \
    };                                                                     \
                                                                           \
    Theory((size_t idx0, size_t idx1), suite,                              \
           swap_##memb_size##byte_elem_theory)                             \
    {                                                                      \
        char buffer[BUFFER_SIZE][memb_size];                               \
                                                                           \
        for (size_t i = 0; i < BUFFER_SIZE; i++) {                         \
            memset(buffer[i], i + 1, memb_size);                           \
        }                                                                  \
                                                                           \
        char memb_buffer[memb_size];                                       \
        char original_idx0[memb_size];                                     \
        char original_idx1[memb_size];                                     \
        memcpy(original_idx0, buffer[idx0], memb_size);                    \
        memcpy(original_idx1, buffer[idx1], memb_size);                    \
                                                                           \
        struct array arr = {buffer, BUFFER_SIZE, sizeof(char[memb_size])}; \
                                                                           \
        swap(&arr, idx0, idx1);                                            \
        cr_assert(eq(chr[memb_size], buffer[idx1], original_idx0));        \
        cr_assert(eq(chr[memb_size], buffer[idx0], original_idx1));        \
        swap(&arr, idx0, idx1);                                            \
        cr_assert(eq(chr[memb_size], buffer[idx0], original_idx0));        \
        cr_assert(eq(chr[memb_size], buffer[idx1], original_idx1));        \
        swap_with_mbuffer(&arr, memb_buffer, idx0, idx1);                  \
        cr_assert(eq(chr[memb_size], buffer[idx1], original_idx0));        \
        cr_assert(eq(chr[memb_size], buffer[idx0], original_idx1));        \
        swap_with_mbuffer(&arr, memb_buffer, idx0, idx1);                  \
        cr_assert(eq(chr[memb_size], buffer[idx0], original_idx0));        \
        cr_assert(eq(chr[memb_size], buffer[idx1], original_idx1));        \
    }

SWAP_TESTS(1)
SWAP_TESTS(2)
SWAP_TESTS(30)
SWAP_TESTS(64)
SWAP_TESTS(100)
SWAP_TESTS(128)
SWAP_TESTS(129)

#undef suite
