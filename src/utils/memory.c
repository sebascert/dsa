#include <string.h>

#include "dsa/utils/memory.h"

bool is_arr_null(struct array* arr) {
    return !arr || !arr->buffer || arr->size == 0 || arr->memb_size == 0;
}

int swap(struct array* arr, size_t idx_a, size_t idx_b) {
    if (is_arr_null(arr)) return 1;
    if (idx_a >= arr->size || idx_b >= arr->size) return 1;
    if (idx_a == idx_b) return 0;

    unsigned char buf[SWAP_SIZE];

    unsigned char* p1 = buf_idx(arr->buffer, idx_a, arr->memb_size);
    unsigned char* p2 = buf_idx(arr->buffer, idx_b, arr->memb_size);

    size_t left = arr->memb_size;
    while (left > SWAP_SIZE) {
        memcpy(buf, p1, SWAP_SIZE);
        memcpy(p1, p2, SWAP_SIZE);
        memcpy(p2, buf, SWAP_SIZE);

        left -= SWAP_SIZE;
        p1 += SWAP_SIZE;
        p2 += SWAP_SIZE;
    }

    memcpy(buf, p1, left);
    memcpy(p1, p2, left);
    memcpy(p2, buf, left);

    return 0;
}

int swap_with_mbuffer(struct array* arr, void* memb_buffer, size_t idx_a,
                      size_t idx_b) {
    if (is_arr_null(arr)) return 1;
    if (!memb_buffer) return 1;
    if (idx_a >= arr->size || idx_b >= arr->size) return 1;
    if (idx_a == idx_b) return 0;

    unsigned char* p1 = buf_idx(arr->buffer, idx_a, arr->memb_size);
    unsigned char* p2 = buf_idx(arr->buffer, idx_b, arr->memb_size);

    memcpy(memb_buffer, p1, arr->memb_size);
    memcpy(p1, p2, arr->memb_size);
    memcpy(p2, memb_buffer, arr->memb_size);

    return 0;
}
