#include "dsa/utils/allocator.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>

#define suite utils_allocator

ParameterizedTestParameters(suite, fail_allocator)
{
    static size_t params[] = {0, 1, 2, 4, 5, 100};
    return cr_make_param_array(size_t, params, sizeof(params) / sizeof(size_t));
}

ParameterizedTest(size_t* param, suite, fail_allocator)
{
    cr_assert(eq(ptr, fail_allocator.malloc(*param), NULL));
    cr_assert(eq(ptr, fail_allocator.realloc(NULL, *param), NULL));

    fail_alloc_realloc_ptr_size = *param + 1;
    cr_assert(eq(ptr, fail_allocator.realloc((void*)1, *param), (void*)1));
    fail_alloc_realloc_ptr_size = *param;
    cr_assert(eq(ptr, fail_allocator.realloc((void*)1, *param), (void*)1));

    if (*param > 0) {
        fail_alloc_realloc_ptr_size = *param - 1;
        cr_assert(eq(ptr, fail_allocator.realloc((void*)1, *param), NULL));
    }
}

#undef suite
