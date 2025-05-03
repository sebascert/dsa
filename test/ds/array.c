#include "dsa/ds/array.h"

#include "dsa/core/utils/memory.h"
#include "dsa/utils/allocator.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#include <string.h>

#define suite ds_array

void set_array(struct array* arr, struct array val)
{
    memcpy(arr, &val, sizeof(struct array));
}

Test(suite, new)
{
    struct array arr;

    // assert invalid arg cases
    set_array(&arr, array_new(0, 1));
    cr_assert(array_is_null(&arr));
    set_array(&arr, array_new(1, 0));
    cr_assert(array_is_null(&arr));

    set_array(&arr, array_new(1, 1));
    cr_assert(not(array_is_null(&arr)));
    array_free(&arr);
}

Test(suite, new_with_alloc)
{
    struct array arr;

    // assert invalid arg cases
    set_array(&arr, array_new_with_alloc(0, 1, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    set_array(&arr, array_new_with_alloc(1, 0, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    set_array(&arr, array_new_with_alloc(1, 0, NULL));
    cr_assert(array_is_null(&arr));

    // assert invalid allocation
    set_array(&arr, array_new_with_alloc(1, 1, &fail_allocator));
    cr_assert(array_is_null(&arr));

    set_array(&arr, array_new_with_alloc(1, 1, &stdlib_allocator));
    cr_assert(not(array_is_null(&arr)));
    array_free(&arr);
}

Test(suite, free)
{
    struct array arr;

    // no signal raised
    set_array(&arr, NULL_ARRAY);
    array_free(&arr);

    // assert array is nulled after free
    set_array(&arr, array_new(1, 1));
    array_free(&arr);
    cr_assert(array_is_null(&arr));
}

Test(suite, is_null)
{
    cr_assert(array_is_null(&NULL_ARRAY));
}

Test(suite, from_buffer)
{
    char buffer[1];
    struct array arr;

    // invalid arguments
    set_array(&arr, array_from_buffer(NULL, 1, 1, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    set_array(&arr, array_from_buffer(&buffer, 0, 1, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    set_array(&arr, array_from_buffer(&buffer, 1, 0, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    set_array(&arr, array_from_buffer(&buffer, 1, 1, NULL));
    cr_assert(array_is_null(&arr));

    set_array(&arr, array_from_buffer(&buffer, 1, 1, &stdlib_allocator));
    cr_assert(not(array_is_null(&arr)));
}

Test(suite, swap)
{
    struct array arr = array_new(1, 1);

    cr_assert(eq(int, array_swap(&arr, 0, 0), 0));
    cr_assert(eq(int, array_swap(NULL, 0, 0), 1));
    cr_assert(eq(int, array_swap(&arr, 0, 1), 2));
    cr_assert(eq(int, array_swap(&arr, 1, 0), 2));
}

Test(suite, swap_with_mbuffer)
{
    char memb_buffer;
    struct array arr = array_new(1, 1);

    cr_assert(eq(int, array_swap_with_mbuffer(&arr, &memb_buffer, 0, 0), 0));
    cr_assert(eq(int, array_swap_with_mbuffer(NULL, &memb_buffer, 0, 0), 1));
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, &memb_buffer, 0, 1), 2));
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, &memb_buffer, 1, 0), 2));
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, NULL, 0, 0), 3));
}

#define SWAP_TEST_BUFFER_SIZE 5
#define BUFFER_INDICES 0, 1, 2, 3, 4
#define SWAP_TEST(memb_size)                                               \
    TheoryDataPoints(suite, swap_##memb_size##byte_elem_theory) = {        \
        DataPoints(size_t, BUFFER_INDICES),                                \
        DataPoints(size_t, BUFFER_INDICES),                                \
    };                                                                     \
                                                                           \
    Theory((size_t idx0, size_t idx1), suite,                              \
           swap_##memb_size##byte_elem_theory)                             \
    {                                                                      \
        struct array arr = array_new(SWAP_TEST_BUFFER_SIZE, memb_size);    \
                                                                           \
        for (size_t i = 0; i < SWAP_TEST_BUFFER_SIZE; i++) {               \
            memset(buf_idx(arr.buffer, i, memb_size), 'a' + i, memb_size); \
        }                                                                  \
                                                                           \
        void* idx0_ptr = buf_idx(arr.buffer, idx0, memb_size);             \
        void* idx1_ptr = buf_idx(arr.buffer, idx1, memb_size);             \
        char memb_buffer[memb_size];                                       \
        char original_idx0[memb_size], original_idx1[memb_size];           \
        memcpy(original_idx0, idx0_ptr, memb_size);                        \
        memcpy(original_idx1, idx1_ptr, memb_size);                        \
                                                                           \
        array_swap(&arr, idx0, idx1);                                      \
        cr_assert(eq(chr[memb_size], idx1_ptr, original_idx0));            \
        cr_assert(eq(chr[memb_size], idx0_ptr, original_idx1));            \
        array_swap(&arr, idx0, idx1);                                      \
        cr_assert(eq(chr[memb_size], idx0_ptr, original_idx0));            \
        cr_assert(eq(chr[memb_size], idx1_ptr, original_idx1));            \
        array_swap_with_mbuffer(&arr, memb_buffer, idx0, idx1);            \
        cr_assert(eq(chr[memb_size], idx1_ptr, original_idx0));            \
        cr_assert(eq(chr[memb_size], idx0_ptr, original_idx1));            \
        array_swap_with_mbuffer(&arr, memb_buffer, idx0, idx1);            \
        cr_assert(eq(chr[memb_size], idx0_ptr, original_idx0));            \
        cr_assert(eq(chr[memb_size], idx1_ptr, original_idx1));            \
    }

SWAP_TEST(1)
SWAP_TEST(2)
SWAP_TEST(30)
SWAP_TEST(64)
SWAP_TEST(100)
SWAP_TEST(128)
SWAP_TEST(129)

#undef suite
