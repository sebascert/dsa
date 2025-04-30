#include "dsa/utils/allocator.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#define suite utils_allocator

TheoryDataPoints(suite, fail_allocator) = {
    DataPoints(size_t, 0, 1, 2, 4, 5, 100),
};
Theory((size_t size), suite, fail_allocator)
{
    cr_assert(eq(ptr, fail_allocator.malloc(size), NULL));
    cr_assert(eq(ptr, fail_allocator.realloc(NULL, size), NULL));

    fail_alloc_realloc_ptr_size = size + 1;
    cr_assert(eq(ptr, fail_allocator.realloc((void*)1, size), (void*)1));
    fail_alloc_realloc_ptr_size = size;
    cr_assert(eq(ptr, fail_allocator.realloc((void*)1, size), (void*)1));

    if (size > 0) {
        fail_alloc_realloc_ptr_size = size - 1;
        cr_assert(eq(ptr, fail_allocator.realloc((void*)1, size), NULL));
    }
}

#undef suite
