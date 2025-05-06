#include "dsa/utils/allocator.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#define suite utils_allocator

#define VALID_PTR (void*)1

TheoryDataPoints(suite, fail_allocator) = {
    DataPoints(size_t, 0, 1, 2, 4, 5, 100),
};
Theory((size_t size), suite, fail_allocator)
{
    // memory is never allocated
    cr_assert(eq(ptr, fail_allocator.malloc(size), NULL));
    cr_assert(eq(ptr, fail_allocator.realloc(NULL, size), NULL));

    // reallocation to lesser size simulates nop or freeing
    fail_alloc_realloc_ptr_size = size + 1;
    cr_assert(eq(ptr, fail_allocator.realloc(VALID_PTR, size), VALID_PTR));
    fail_alloc_realloc_ptr_size = size;
    cr_assert(eq(ptr, fail_allocator.realloc(VALID_PTR, size), VALID_PTR));

    // reallocation to bigger size fails
    if (size > 0) {
        fail_alloc_realloc_ptr_size = size - 1;
        cr_assert(eq(ptr, fail_allocator.realloc(VALID_PTR, size), NULL));
    }
}

#undef suite
