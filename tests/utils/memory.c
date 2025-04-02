#include <criterion/criterion.h>
#include <criterion/internal/new_asserts.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "utils/memory.h"

#define suite utils_memory

Test(suite, buffer_index) {
    int arr[5] = {0, 1, 2, 3, 4};
    int* arr_ptr = arr;
    void* buffer = arr;

    for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++, arr_ptr++) {
        cr_assert(eq(int, arr[i], *(int*)BUF_IDX(buffer, i, sizeof(int))));
        cr_assert(eq(ptr, arr_ptr, BUF_IDX(buffer, i, sizeof(int))));
    }
}

Test(suite, buffer_increment) {
    int arr[5] = {0, 1, 2, 3, 4};
    int* arr_ptr = arr;
    void* buffer = arr;

    for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++, arr_ptr++) {
        cr_assert(eq(int, arr[i], *(int*)buffer));
        cr_assert(eq(ptr, arr_ptr, buffer));
        BUF_INC(buffer, 1, sizeof(int));
    }
}

#define SWAP_THEORY_DEF(memb_size)                                      \
    TheoryDataPoints(suite, buffer_swap_##memb_size##byte_theory) = {   \
        DataPoints(size_t, 0, 1, 2, 3, 4),                              \
        DataPoints(size_t, 0, 1, 2, 3, 4),                              \
    };                                                                  \
                                                                        \
    Theory((size_t idx0, size_t idx1), suite,                           \
           buffer_swap_##memb_size##byte_theory) {                      \
        char buffer[5][memb_size];                                      \
                                                                        \
        for (size_t i = 0; i < 5; i++) {                                \
            memset(buffer[i], i + 1, memb_size);                        \
        }                                                               \
                                                                        \
        char original_idx0[memb_size];                                  \
        char original_idx1[memb_size];                                  \
        memcpy(original_idx0, buffer[idx0], memb_size);                 \
        memcpy(original_idx1, buffer[idx1], memb_size);                 \
                                                                        \
        swap_buffer_elems(buffer, sizeof(char[memb_size]), idx0, idx1); \
                                                                        \
        /* Validate swap happened correctly */                          \
        cr_assert_arr_eq(buffer[idx1], original_idx0, memb_size);       \
        cr_assert_arr_eq(buffer[idx0], original_idx1, memb_size);       \
    }

SWAP_THEORY_DEF(1)
SWAP_THEORY_DEF(2)
SWAP_THEORY_DEF(30)
SWAP_THEORY_DEF(64)
SWAP_THEORY_DEF(100)
SWAP_THEORY_DEF(128)
SWAP_THEORY_DEF(129)

#undef suite
