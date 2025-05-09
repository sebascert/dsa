#include "dsa/test_utils/assertions.h"

#include "dsa/core/utils/memory.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

void cr_assert_eq_mem(void* buf_a, void* buf_b, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        cr_assert(eq(chr, *((char*)buf_idx(buf_a, i, 1)),
                     *((char*)buf_idx(buf_b, i, 1))),
                  "cr_assert_eq_mem: diff in byte %zu", i);
    }
}
