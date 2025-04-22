/**
 * \file dsa/types/allocator.h
 * \brief Allocator type.
 */

#ifndef DSA_TYPES_ALLOCATOR_H
#define DSA_TYPES_ALLOCATOR_H

#include <memory.h>
#include <stdlib.h>

typedef void* (*Malloc)(size_t);
typedef void* (*Realloc)(void*, size_t);
typedef void (*Free)(void*);

/**
 * \brief Allocator type.
 *
 * An allocator is a container which provides the core interface for a memory
 * allocator.
 */
struct allocator {
    Malloc malloc;   /**< allocate n bytes buffer */
    Realloc realloc; /**< realloc buffer into n bytes */
    Free free;       /**< free allocated buffer */
};

/**
 * \brief C STD library allocator structure constant
 *
 * Contains the allocation functions provided in the C stdlib
 */
extern const struct allocator stdlib_allocator;

#endif /* ifndef DSA_TYPES_ALLOCATOR_H */
