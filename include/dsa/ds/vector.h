/**
 * \file dsa/ds/vector.h
 * \brief Vector data structure header.
 */

#ifndef DSA_DS_VECTOR_H
#define DSA_DS_VECTOR_H

#include "dsa/ds/array.h"
#include "dsa/types/allocator.h"
#include "dsa/types/growth.h"

#include <stdbool.h>

/**
 * \brief Vector data structure.
 *
 * A vector is a dynamic array backed by an underlying array. It can be resized
 * manually or automatically using a specified growth strategy.
 */
struct vector;

/**
 * \brief Null vector constant.
 */
extern const struct vector NULL_VECTOR;

/**
 * \brief Create new vector.
 *
 * Allocates array of size (size * memb_size) bytes plus memb_buffer of size
 * memb_size bytes with the stdlib allocator, and initializes vector capacity to
 * size and vector data as empty (size = 0).
 *
 * \param size Initial capacity of the vector.
 * \param memb_size Vector member size.
 * \param growth Resizing growth function.
 *
 * \return Created vector, or NULL_VECTOR if the allocation fails or any
 * parameter is invalid.
 */
struct vector vector_new(size_t size, size_t memb_size, Growth growth);

/**
 * \brief Create new vector with given allocator.
 *
 * Allocates array of size (size * memb_size) bytes plus memb_buffer of size
 * memb_size bytes with the given allocator, and initializes vector capacity to
 * size and vector data as empty (size = 0).
 *
 * \param size Initial capacity of the vector.
 * \param memb_size Container member size.
 * \param growth Resizing growth function.
 * \param alloc Allocator.
 *
 * \return Created vector, or NULL_VECTOR if the allocation fails or any
 * parameter is invalid.
 */
struct vector vector_new_with_alloc(size_t size, size_t memb_size,
                                    Growth growth,
                                    const struct allocator* alloc);

/**
 * \brief Free vector.

 * Does nothing if the vector is null, overwrites vector to null after freeing
 it.
 *
 * \param vec Vector.
 */
void vector_free(struct vector* vec);

/**
 * \brief Evaluate nullness of vector.
 *
 * \param vec Vector.
 *
 * \return True if the vector is NULL, false otherwise.
 */
bool vector_is_null(const struct vector* vec);

/**
 * \brief Create new vector from [array](\ref array).
 *
 * overwrites arr to null after vector creation.
 *
 * \param arr Array.
 * \param growth Resizing growth function.
 *
 * \return Created vector, or NULL_VECTOR if any parameter is invalid.
 */
struct vector vector_from_array(struct array* arr, Growth growth);

/**
 * \brief Get vector's underlying array.
 *
 * \param vec Vector.
 *
 * \return Constant reference to vector's underlying array, or NULL if the
 * vector is null.
 */
const struct array* vector_to_array(struct vector* vec);

/**
 * \brief Index element in vector.
 *
 * \param vec Vector.
 * \param idx Index.
 *
 * \return Pointer to element at index or NULL if the vector is NULL or
 * index out of bounds.
 */
void* vector_index(const struct vector* vec, size_t idx);

/**
 * \brief Swap elements at indices in vector.
 *
 * Elements are swapped by value.
 *
 * \param vec Vector.
 * \param idx_a Index a.
 * \param idx_b Index b.
 *
 * \retval 0 Swap succeeded.
 * \retval 1 Null vector.
 * \retval 2 Index out of bounds.
 */
int vector_swap(struct vector* vec, size_t idx_a, size_t idx_b);

/**
 * \brief Insert element at index in vector.
 *
 * Remaining elements are displaced to the right, if the vector is full,
 * capacity grows by growth strategy.
 *
 * \param vec Vector.
 * \param elem Pointer to elem of size memb_size.
 * \param idx Index.
 *
 * \retval 0 Insert succeeded.
 * \retval 1 Null vector.
 * \retval 2 Index out of bounds.
 * \retval 3 Reallocation failed.
 * \retval 4 Null elem.
 */
int vector_insert(struct vector* vec, const void* elem, size_t idx);

/**
 * \brief Remove element at index in vector.
 *
 * Remaining elements are displaced to the left, capacity remains the same.
 *
 * \param vec Vector.
 * \param idx Index.

 * \retval 0 Remove succeeded.
 * \retval 1 Null vector.
 * \retval 2 Index out of bounds.
 */
int vector_remove(struct vector* vec, size_t idx);

/**
 * \brief Append element after last index to vector.
 *
 * If the vector is full, capacity grows by growth strategy.
 *
 * \param vec Vector.
 * \param elem Pointer to elem of size memb_size.
 *
 * \retval 0 Append succeeded.
 * \retval 1 Null vector
 * \retval 3 Reallocation failed.
 * \retval 4 Null elem.
 */
int vector_append(struct vector* vec, const void* elem);

/**
 * \brief Pop last element from vector.
 *
 * Fails if the vector is empty, capacity remains the same.
 *
 * \param vec Vector.
 *
 * \retval 0 Pop succeeded.
 * \retval 1 Null vector
 * \retval 2 Empty vector
 */
int vector_pop(struct vector* vec);

/**
 * \brief Evaluate if size is greater than vector's capacity.
 *
 * \param vec Vector.
 * \param size Test size.
 *
 * \return True if the vector is null or the size is greater than the vector's
 * capacity, false otherwise.
 */
bool vector_overflow(struct vector* vec, size_t size);

/**
 * \brief Set vector size.
 *
 * If the new size overflows the capacity, capacity grows by growth strategy,
 * if the new size is less than current, the size is decreased to the new size,
 * but truncated elements remain unchanged in the underlying array.
 *
 * \param vec Vector.
 * \param size New size.
 *
 * \retval 0 Size set succeeded.
 * \retval 1 Null vector.
 * \retval 2 Reallocation failed.
 */
int vector_set_size(struct vector* vec, size_t size);

/**
 * \brief Set vector capacity.
 *
 * Reallocates array exactly to the new capacity, if size is greater than the
 * new capacity, size is set to new the new capacity and remaining elements are
 * freed, if the given capacity is 0, an error is returned.
 *
 * \param vec Vector.
 * \param capacity New capacity.
 *
 * \retval 0 Capacity set succeeded.
 * \retval 1 Null vector.
 * \retval 2 Reallocation failed.
 * \retval 3 Invalid new capacity of value 0.
 */
int vector_set_capacity(struct vector* vec, size_t capacity);

struct vector {
    size_t size;
    void* memb_buffer;
    const Growth growth;
    struct array arr;
};

#endif /* ifndef DSA_DS_VECTOR_H */
