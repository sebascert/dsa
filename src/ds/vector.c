#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dsa/ds/vector.h"
#include "dsa/types/array.h"
#include "dsa/utils/memory.h"

struct vector vector_new(size_t size, size_t memb_size, Growth growth) {
    return vector_new_with_allocator(size, memb_size, growth,
                                     &stdlib_allocator);
}

struct vector vector_new_with_allocator(size_t size, size_t memb_size,
                                        Growth growth,
                                        const struct allocator* alloc) {
    if (size == 0 || memb_size == 0 || !growth || !alloc) return NULL_VECTOR;

    void* memb_buffer = alloc->malloc(memb_size);
    if (!memb_buffer) return NULL_VECTOR;

    void* buffer = alloc->malloc(size * memb_size);
    if (!buffer) {
        alloc->free(memb_buffer);
        return NULL_VECTOR;
    }

    return (struct vector){
        .size = size,
        .memb_buffer = memb_buffer,
        .growth = growth,
        .arr = {.buffer = buffer, .size = size, .memb_size = memb_size},
        .alloc = alloc,
    };
}

void vector_free(struct vector* vec) {
    vec->alloc->free(vec->memb_buffer);
    vec->alloc->free(vec->arr.buffer);
    memcpy(vec, &NULL_VECTOR, sizeof(struct vector));
}

struct vector vector_from_array(struct array* arr, Growth growth,
                                const struct allocator* alloc) {
    if (is_arr_null(arr) || !growth || !alloc) return NULL_VECTOR;

    void* memb_buffer = alloc->malloc(arr->memb_size);
    if (!memb_buffer) return NULL_VECTOR;

    struct array vec_arr = *arr;
    memcpy(arr, &NULL_ARRAY, sizeof(struct array));

    return (struct vector){
        .size = arr->size,
        .memb_buffer = memb_buffer,
        .growth = growth,
        .arr = vec_arr,
        .alloc = alloc,
    };
}

const struct array* vector_to_array(struct vector* vec) {
    return &vec->arr;
}

void* vector_index(const struct vector* vec, size_t idx) {
    if (vec->size >= idx) return NULL;
    return buf_idx(vec->arr.buffer, idx, vec->arr.memb_size);
}

int vector_swap(struct vector* vec, size_t idx_a, size_t idx_b) {
    void *a, *b;
    if (!(a = vector_index(vec, idx_a)) || !(b = vector_index(vec, idx_b)))
        return 1;

    swap_with_mbuffer(&vec->arr, vec->memb_buffer, idx_a, idx_b);

    return 0;
}

int vector_insert(struct vector* vec, void* elem, size_t idx) {
    void* indexed;
    if (!elem || (!(indexed = vector_index(vec, idx)) && idx != vec->size))
        return 1;

    if (!vector_resize(vec, vec->size + 1)) return 1;

    size_t memb_size = vec->arr.memb_size;

    // insert in between the buffer, move elements 1 position over
    if (indexed)
        memmove(buf_idx(indexed, 1, memb_size), indexed,
                memb_size * (vec->size - idx));
    else
        indexed = buf_idx(vec->arr.buffer, idx, memb_size);

    memcpy(indexed, elem, memb_size);

    vec->size++;
    return 0;
}

int vector_remove(struct vector* vec, size_t idx) {
    void* indexed;
    if (!(indexed = vector_index(vec, idx))) return 1;

    vec->size--;

    if (idx == vec->size - 1) return 0;

    memmove(indexed, buf_idx(indexed, 1, vec->arr.memb_size),
            vec->arr.memb_size * (vec->size - idx));
    return 0;
}

int vector_append(struct vector* vec, void* elem) {
    return vector_insert(vec, elem, vec->size);
}

int vector_pop(struct vector* vec) {
    return vector_remove(vec, vec->size - 1);
}

static inline bool vector_overflow(struct vector* vec, size_t size) {
    return size > vec->arr.size;
}

int vector_resize(struct vector* vec, size_t size) {
    if (!vector_overflow(vec, size)) {
        vec->size = size;
        return 0;
    }

    size_t capacity = vec->arr.size;
    while (size > capacity) {
        capacity = vec->growth(capacity);
    }

    void* buffer =
        vec->alloc->realloc(vec->arr.buffer, vec->arr.memb_size * capacity);
    if (!buffer) return 1;

    vec->size = size;
    vec->arr.buffer = buffer;
    vec->arr.size = capacity;

    return 0;
}

int vector_reserve(struct vector* vec, size_t capacity) {
    if (capacity == 0) return 1;

    void* buffer =
        vec->alloc->realloc(vec->arr.buffer, vec->arr.memb_size * capacity);
    if (!buffer) return 1;

    vec->arr.buffer = buffer;
    vec->arr.size = capacity;

    if (vec->size > capacity) vec->size = capacity;

    return 0;
}
