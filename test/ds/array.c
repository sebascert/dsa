#include "dsa/ds/array.h"

#include "dsa/core/utils/memory.h"
#include "dsa/test_utils/assertions.h"
#include "dsa/utils/allocator.h"
#include "dsa/utils/memory.h"

#include <criterion/criterion.h>
#include <criterion/internal/new_asserts.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#include <stdlib.h>
#include <string.h>

#define suite ds_array

static MEMCPY_TYPE_DEF(struct array, cpyarr);

Test(suite, new)
{
    struct array arr;

    // invalid arg cases
    cpyarr(&arr, array_new(0, 1));
    cr_assert(array_is_null(&arr));
    cpyarr(&arr, array_new(1, 0));
    cr_assert(array_is_null(&arr));

    // valid args case evaluates non null
    cpyarr(&arr, array_new(1, 1));
    cr_assert(not(array_is_null(&arr)));
    array_free(&arr);
}

Test(suite, new_with_alloc)
{
    struct array arr;

    // invalid arg cases
    cpyarr(&arr, array_new_with_alloc(0, 1, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    cpyarr(&arr, array_new_with_alloc(1, 0, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    cpyarr(&arr, array_new_with_alloc(1, 0, NULL));
    cr_assert(array_is_null(&arr));

    // invalid allocation
    cpyarr(&arr, array_new_with_alloc(1, 1, &fail_allocator));
    cr_assert(array_is_null(&arr));

    // valid args case evaluates non null
    cpyarr(&arr, array_new_with_alloc(1, 1, &stdlib_allocator));
    cr_assert(not(array_is_null(&arr)));
    array_free(&arr);
}

Test(suite, free)
{
    struct array arr;

    // no signal raised upon freeing null array
    cpyarr(&arr, NULL_ARRAY);
    array_free(&arr);

    // array is nulled after free
    cpyarr(&arr, array_new(1, 1));
    array_free(&arr);
    cr_assert(array_is_null(&arr));
}

Test(suite, is_null)
{
    // null constant evaluates to null
    cr_assert(array_is_null(&NULL_ARRAY));
}

Test(suite, from_buffer)
{
    char buffer[1];
    struct array arr;

    // invalid arg cases
    cpyarr(&arr, array_from_buffer(NULL, 1, 1, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    cpyarr(&arr, array_from_buffer(&buffer, 0, 1, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    cpyarr(&arr, array_from_buffer(&buffer, 1, 0, &stdlib_allocator));
    cr_assert(array_is_null(&arr));
    cpyarr(&arr, array_from_buffer(&buffer, 1, 1, NULL));
    cr_assert(array_is_null(&arr));

    // valid args case evaluates non null
    cpyarr(&arr, array_from_buffer(&buffer, 1, 1, &stdlib_allocator));
    cr_assert(not(array_is_null(&arr)));
}

Test(suite, swap_api)
{
    struct array arr = array_new(1, 1);

    // exit codes
    cr_assert(eq(int, array_swap(&arr, 0, 0), 0));
    cr_assert(eq(int, array_swap(NULL, 0, 0), 1));
    cr_assert(eq(int, array_swap(&arr, 0, 1), 2));
    cr_assert(eq(int, array_swap(&arr, 1, 0), 2));

    array_free(&arr);
}

Test(suite, swap_with_mbuffer_api)
{
    char memb_buffer;
    struct array arr = array_new(1, 1);

    // exit code cases
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, &memb_buffer, 0, 0), 0));
    cr_assert(eq(int, array_swap_with_mbuffer(NULL, &memb_buffer, 0, 0), 1));
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, &memb_buffer, 0, 1), 2));
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, &memb_buffer, 1, 0), 2));
    cr_assert(eq(int, array_swap_with_mbuffer(&arr, NULL, 0, 0), 3));

    array_free(&arr);
}

// test the swap functions on different given memb_size member size
#define SWAP_TEST_BUFFER_SIZE 5
#define BUFFER_INDICES 0, 1, 2, 3, 4
#define SWAP_THEORY_DEF(memb_size)                                          \
    static struct array swap_##memb_size##byte_arr;                         \
    static void swap_##memb_size##byte_init()                               \
    {                                                                       \
        struct array* arr = &swap_##memb_size##byte_arr;                    \
        cpyarr(arr, array_new(SWAP_TEST_BUFFER_SIZE, memb_size));           \
                                                                            \
        for (size_t i = 0; i < SWAP_TEST_BUFFER_SIZE; i++) {                \
            memset(buf_idx(arr->buffer, i, memb_size), 'a' + i, memb_size); \
        }                                                                   \
    }                                                                       \
    static void swap_##memb_size##byte_fini()                               \
    {                                                                       \
        array_free(&swap_##memb_size##byte_arr);                            \
    }                                                                       \
    TheoryDataPoints(suite, swap_##memb_size##byte) = {                     \
        DataPoints(size_t, BUFFER_INDICES),                                 \
        DataPoints(size_t, BUFFER_INDICES),                                 \
    };                                                                      \
    Theory((size_t idx0, size_t idx1), suite, swap_##memb_size##byte,       \
           .init = swap_##memb_size##byte_init,                             \
           .fini = swap_##memb_size##byte_fini)                             \
    {                                                                       \
        struct array* arr = &swap_##memb_size##byte_arr;                    \
                                                                            \
        void* idx0_ptr = buf_idx(arr->buffer, idx0, memb_size);             \
        void* idx1_ptr = buf_idx(arr->buffer, idx1, memb_size);             \
        char memb_buffer[memb_size];                                        \
        char original_idx0[memb_size], original_idx1[memb_size];            \
        memcpy(original_idx0, idx0_ptr, memb_size);                         \
        memcpy(original_idx1, idx1_ptr, memb_size);                         \
                                                                            \
        /*swap correctness*/                                                \
        array_swap(arr, idx0, idx1);                                        \
        cr_assert_eq_mem(idx1_ptr, original_idx0, memb_size);               \
        cr_assert_eq_mem(idx0_ptr, original_idx1, memb_size);               \
        array_swap(arr, idx0, idx1);                                        \
        cr_assert_eq_mem(idx0_ptr, original_idx0, memb_size);               \
        cr_assert_eq_mem(idx1_ptr, original_idx1, memb_size);               \
        array_swap_with_mbuffer(arr, memb_buffer, idx0, idx1);              \
        cr_assert_eq_mem(idx1_ptr, original_idx0, memb_size);               \
        cr_assert_eq_mem(idx0_ptr, original_idx1, memb_size);               \
        array_swap_with_mbuffer(arr, memb_buffer, idx0, idx1);              \
        cr_assert_eq_mem(idx0_ptr, original_idx0, memb_size);               \
        cr_assert_eq_mem(idx1_ptr, original_idx1, memb_size);               \
    }

SWAP_THEORY_DEF(1)
SWAP_THEORY_DEF(2)
SWAP_THEORY_DEF(30)
SWAP_THEORY_DEF(64)
SWAP_THEORY_DEF(100)
SWAP_THEORY_DEF(128)
SWAP_THEORY_DEF(129)

#undef suite
