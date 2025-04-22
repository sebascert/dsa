#include "dsa/ds/array.h"

#include "dsa/types/allocator.h"
#include "dsa/utils/memory.h"

#include <string.h>

const struct array NULL_ARRAY = {
    .buffer = NULL,
    .size = 0,
    .memb_size = 0,
    .alloc = NULL,
};

struct array array_new(size_t size, size_t memb_size)
{
    return array_new_with_alloc(size, memb_size, &stdlib_allocator);
}

struct array array_new_with_alloc(size_t size, size_t memb_size,
                                  const struct allocator* alloc)
{
    if (size == 0 || memb_size == 0)
        return NULL_ARRAY;

    void* buffer = alloc->malloc(size * memb_size);
    if (!buffer)
        return NULL_ARRAY;

    return (struct array){
        .buffer = buffer,
        .size = size,
        .memb_size = memb_size,
        .alloc = alloc,
    };
}

void array_free(struct array* arr)
{
    if (array_is_null(arr))
        return;

    arr->alloc->free(arr->buffer);
    memcpy(arr, &NULL_ARRAY, sizeof(struct array));
}

inline bool array_is_null(struct array* arr)
{
    return !arr || !arr->buffer || arr->size == 0 || arr->memb_size == 0 ||
           !arr->alloc;
}

int array_swap(struct array* arr, size_t idx_a, size_t idx_b)
{
    if (array_is_null(arr))
        return 1;
    if (idx_a >= arr->size || idx_b >= arr->size)
        return 2;
    if (idx_a == idx_b)
        return 0;

    unsigned char buf[ARRAY_SWAP_SIZE];

    unsigned char* p1 = buf_idx(arr->buffer, idx_a, arr->memb_size);
    unsigned char* p2 = buf_idx(arr->buffer, idx_b, arr->memb_size);

    size_t left = arr->memb_size;
    while (left > ARRAY_SWAP_SIZE) {
        memcpy(buf, p1, ARRAY_SWAP_SIZE);
        memcpy(p1, p2, ARRAY_SWAP_SIZE);
        memcpy(p2, buf, ARRAY_SWAP_SIZE);

        left -= ARRAY_SWAP_SIZE;
        p1 += ARRAY_SWAP_SIZE;
        p2 += ARRAY_SWAP_SIZE;
    }

    memcpy(buf, p1, left);
    memcpy(p1, p2, left);
    memcpy(p2, buf, left);

    return 0;
}

int array_swap_with_mbuffer(struct array* arr, void* memb_buffer, size_t idx_a,
                            size_t idx_b)
{
    if (array_is_null(arr))
        return 1;
    if (!memb_buffer)
        return 3;
    if (idx_a >= arr->size || idx_b >= arr->size)
        return 2;
    if (idx_a == idx_b)
        return 0;

    unsigned char* p1 = buf_idx(arr->buffer, idx_a, arr->memb_size);
    unsigned char* p2 = buf_idx(arr->buffer, idx_b, arr->memb_size);

    memcpy(memb_buffer, p1, arr->memb_size);
    memcpy(p1, p2, arr->memb_size);
    memcpy(p2, memb_buffer, arr->memb_size);

    return 0;
}
