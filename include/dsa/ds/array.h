/**
 * \file dsa/ds/array.h
 * \brief Array data structure.
 */

#ifndef DSA_DS_ARRAY_H
#define DSA_DS_ARRAY_H

#include "dsa/types/allocator.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * \brief Array data structure.
 *
 * An array structure serves as an array descriptor, containing a pointer to a
 * buffer, allocator, count of elements and size of elements. The struct
 * definition must not be hidden.
 */
struct array {
    void *buffer;
    size_t size;
    size_t memb_size;
    const struct allocator *const alloc;
};

/**
 * \brief Null array constant.
 */
extern const struct array NULL_ARRAY;

/**
 * \brief Create new array.
 *
 * Allocates buffer of size (size * memb_size) bytes with the stdlib allocator.
 *
 * \param size Initial capacity of the array.
 * \param memb_size Array member size.
 *
 * \return Created array, or NULL_ARRAY if the allocation fails or any parameter
 * is invalid.
 */
struct array array_new(size_t size, size_t memb_size);

/**
 * \brief Create new array with given allocator.
 *
 * Allocates buffer of size (size * memb_size) bytes with the given allocator.
 *
 * \param size Initial capacity of the array.
 * \param memb_size Array member size.
 * \param alloc Allocator.
 *
 * \return Created array, or NULL_ARRAY if the allocation fails or any parameter
 * is invalid.
 */
struct array array_new_with_alloc(size_t size, size_t memb_size,
                                  const struct allocator *alloc);

/**
 * \brief Free array.
 *
 * Does nothing if the array is null, overwrites array to null after freeing it.
 *
 * \param arr Array.
 */
void array_free(struct array *arr);

/**
 * \brief Evaluate nullness of array.
 *
 * \param arr Array.
 *
 * \return True if the array is NULL, false otherwise.
 */
bool array_is_null(const struct array *arr);

/**
 * \brief Swap elements at indices in array.
 *
 * Elements are swapped by value.
 *
 * \param arr Array.
 * \param idx_a Index a.
 * \param idx_b Index b.
 *
 * \retval 0 Swap succeeded.
 * \retval 1 Null array.
 * \retval 2 Index out of bounds.
 */
int array_swap(struct array *arr, size_t idx_a, size_t idx_b);

/**
 * \brief buffer size for internal swap stack buffer `array_swap`.
 *
 * The swap is performed in chunks of the given size.
 */
#define ARRAY_SWAP_SIZE 64

/**
 * \brief Swap elements at indices in array with buffer.
 *
 * Elements are swapped by value, using the given buffer for swapping them.
 *
 * \param arr Array.
 * \param memb_buffer Buffer of memb_size size.
 * \param idx_a Index a.
 * \param idx_b Index b.
 *
 * \retval 0 Swap succeeded.
 * \retval 1 Null array.
 * \retval 2 Index out of bounds.
 * \retval 3 Null memb_buffer.
 */
int array_swap_with_mbuffer(struct array *arr, void *memb_buffer, size_t idx_a,
                            size_t idx_b);

#endif /* ifndef DSA_DS_ARRAY_H */
