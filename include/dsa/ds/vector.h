/*
 * vector data structure
 * the vector data structure provides a dynamic array
 * */

#ifndef DSA_DS_VECTOR_H
#define DSA_DS_VECTOR_H

#include <stdbool.h>

#include "dsa/types/allocator.h"
#include "dsa/types/array.h"
#include "dsa/types/growth.h"

struct vector;

extern const struct vector NULL_VECTOR;

// construct new vector structure with stdlib allocator
struct vector vector_new(size_t size, size_t memb_size, Growth growth);
// construct new vector structure with given allocator
struct vector vector_new_with_allocator(size_t size, size_t memb_size,
                                        Growth growth,
                                        const struct allocator* alloc);
// free vector underlying buffers and null given vector
void vector_free(struct vector* vec);

// construct new vector from array and null given array
struct vector vector_from_array(struct array* arr, Growth growth,
                                const struct allocator* alloc);
// returns pointer to vector underlying array
const struct array* vector_to_array(struct vector* vec);

// index element in vector
// return NULL if out of bounds
void* vector_index(const struct vector* vec, size_t idx);

// swap two elements in vector
int vector_swap(struct vector* vec, size_t idx_a, size_t idx_b);

// insert element at given index in vector displacing remaining elements
// if capacity if overflown, capacity is reallocated to growth(capacity)
int vector_insert(struct vector* vec, void* elem, size_t idx);

// remove element at index given index in vector displacing remaining elements
// never frees memory
int vector_remove(struct vector* vec, size_t idx);

// append element to vector
int vector_append(struct vector* vec, void* elem);

// remove last element from vector
int vector_pop(struct vector* vec);

// check if size would overflow vector underlying array
static inline bool vector_overflow(struct vector* vec, size_t size);

// resizes the vector to given size, reallocates capacity by Growth function
// truncates elements if given size is less than current
// new elements created have garbage values
int vector_resize(struct vector* vec, size_t size);
// reserves the given capacity reallocating underlying array if needed
// truncates elements if given capacity is less than current
// 0 capacity is invalid
int vector_reserve(struct vector* vec, size_t capacity);

struct vector {
    size_t size;
    void* memb_buffer;
    const Growth growth;
    const struct allocator* const alloc;
    struct array arr;
};

#endif /* ifndef DSA_DS_VECTOR_H */
