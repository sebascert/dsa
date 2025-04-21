#ifndef DSA_UTILS_MEMORY_H
#define DSA_UTILS_MEMORY_H

#include "dsa/types/array.h"

#include <stdbool.h>
#include <stddef.h>

// ith index of void pointer buffer by memb_size
#define buf_idx(buffer, i, memb_size) \
    ((void *)((unsigned char *)(buffer) + ((i) * (memb_size))))

// increment void pointer buffer by i by memb_size
#define buf_inc(buffer, i, memb_size) (buffer) = buf_idx(buffer, i, memb_size)

// evaluates true if arr is null, arr buffer is null or sizes are 0
bool is_arr_null(struct array *arr);

int swap(struct array *arr, size_t idx_a, size_t idx_b);
#define SWAP_SIZE 64

int swap_with_mbuffer(struct array *arr, void *memb_buffer, size_t idx_a,
                      size_t idx_b);

#endif /* ifndef DSA_UTILS_MEMORY_H */
