#include "dsa/ds/vector.h"

#include "dsa/utils/memory.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const struct vector NULL_VECTOR = {
    .size = 0,
    .memb_buffer = NULL,
    .growth = NULL,
    .arr = {0},
};

struct vector vector_new(size_t size, size_t memb_size, Growth growth)
{
    return vector_new_with_alloc(size, memb_size, growth, &stdlib_allocator);
}

struct vector vector_new_with_alloc(size_t size, size_t memb_size,
                                    Growth growth,
                                    const struct allocator* alloc)
{
    if (size == 0 || memb_size == 0 || !growth || !alloc)
        return NULL_VECTOR;

    void* memb_buffer = alloc->malloc(memb_size);
    if (!memb_buffer)
        return NULL_VECTOR;

    void* buffer = alloc->malloc(size * memb_size);
    if (!buffer) {
        alloc->free(memb_buffer);
        return NULL_VECTOR;
    }

    return (struct vector){
        .size = size,
        .memb_buffer = memb_buffer,
        .growth = growth,
        .arr =
            {
                .buffer = buffer,
                .size = size,
                .memb_size = memb_size,
                .alloc = alloc,
            },
    };
}

void vector_free(struct vector* vec)
{
    if (vector_is_null(vec))
        return;

    vec->arr.alloc->free(vec->memb_buffer);
    vec->arr.alloc->free(vec->arr.buffer);
    memcpy(vec, &NULL_VECTOR, sizeof(struct vector));
}

inline bool vector_is_null(const struct vector* vec)
{
    return !vec || !vec->memb_buffer || !vec->growth ||
           array_is_null(&vec->arr);
}

struct vector vector_from_array(struct array* arr, Growth growth)
{
    if (array_is_null(arr) || !growth)
        return NULL_VECTOR;

    void* memb_buffer = arr->alloc->malloc(arr->memb_size);
    if (!memb_buffer)
        return NULL_VECTOR;

    struct array vec_arr = *arr;
    memcpy(arr, &NULL_ARRAY, sizeof(struct array));

    return (struct vector){
        .size = arr->size,
        .memb_buffer = memb_buffer,
        .growth = growth,
        .arr = vec_arr,
    };
}

const struct array* vector_to_array(struct vector* vec)
{
    return &vec->arr;
}

void* vector_index(const struct vector* vec, size_t idx)
{
    if (vector_is_null(vec) || vec->size >= idx)
        return NULL;

    return buf_idx(vec->arr.buffer, idx, vec->arr.memb_size);
}

int vector_swap(struct vector* vec, size_t idx_a, size_t idx_b)
{
    if (vector_is_null(vec))
        return 1;
    if (idx_a >= vec->size || idx_b >= vec->size)
        return 2;

    array_swap_with_mbuffer(&vec->arr, vec->memb_buffer, idx_a, idx_b);

    return 0;
}

int vector_insert(struct vector* vec, const void* elem, size_t idx)
{
    if (vector_is_null(vec))
        return 1;
    if (!elem)
        return 4;

    void* indexed = vector_index(vec, idx);
    if (!indexed && idx != vec->size)
        return 2;

    if (vector_set_size(vec, vec->size + 1) != 0)
        return 3;

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

int vector_remove(struct vector* vec, size_t idx)
{
    if (vector_is_null(vec))
        return 1;

    void* indexed = vector_index(vec, idx);
    if (!indexed)
        return 2;

    vec->size--;

    if (idx == vec->size - 1)
        return 0;

    memmove(indexed, buf_idx(indexed, 1, vec->arr.memb_size),
            vec->arr.memb_size * (vec->size - idx));
    return 0;
}

int vector_append(struct vector* vec, const void* elem)
{
    return vector_insert(vec, elem, vec->size);
}

int vector_pop(struct vector* vec)
{
    return vector_remove(vec, vec->size - 1);
}

inline bool vector_overflow(struct vector* vec, size_t size)
{
    return vector_is_null(vec) || size > vec->arr.size;
}

int vector_set_size(struct vector* vec, size_t size)
{
    if (vector_is_null(vec))
        return 1;
    if (!vector_overflow(vec, size)) {
        vec->size = size;
        return 0;
    }

    size_t new_capacity = vec->arr.size;
    while (size > new_capacity) {
        new_capacity = vec->growth(new_capacity);
    }

    void* buffer = vec->arr.alloc->realloc(vec->arr.buffer,
                                           vec->arr.memb_size * new_capacity);
    if (!buffer)
        return 2;

    vec->size = size;
    vec->arr.buffer = buffer;
    vec->arr.size = new_capacity;

    return 0;
}

int vector_set_capacity(struct vector* vec, size_t capacity)
{
    if (vector_is_null(vec))
        return 1;
    if (capacity == 0)
        return 3;

    void* buffer =
        vec->arr.alloc->realloc(vec->arr.buffer, vec->arr.memb_size * capacity);
    if (!buffer)
        return 2;

    vec->arr.buffer = buffer;
    vec->arr.size = capacity;

    if (vec->size > capacity)
        vec->size = capacity;

    return 0;
}
