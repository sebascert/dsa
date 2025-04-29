/**
 * \file dsa/utils/allocator.h
 * \brief Debug and utils allocators.
 */

#ifndef DSA_UTILS_ALLOCATOR_H
#define DSA_UTILS_ALLOCATOR_H

#include "dsa/types/allocator.h"

/** \brief Size of the next ptr passed to fail_allocator->realloc
 *
 * Used to mock the 2 cases on reallocation, when the ptr size is less than the
 * reallocated size, the case is of memory allocation, otherwise it would be of
 * memory freeing.
 */
static size_t fail_alloc_realloc_ptr_size;

static void* fail_alloc_malloc(size_t size)
{
    (void)size;
    return NULL;
}
static void* fail_alloc_realloc(void* ptr, size_t size)
{
    if (!ptr)
        return NULL;
    return size > fail_alloc_realloc_ptr_size ? NULL : ptr;
}
static void fail_alloc_free(void* buffer)
{
    (void)buffer;
    return;
}

/**
 * \brief Fail allocator structure constant.
 *
 * Mocks an allocator which always fails to allocate new memory, malloc and
 * reallocating to bigger size always return NULL, freeing and reallocating to
 * smaller size does nothing.
 */
static const struct allocator fail_allocator = {
    /// \cond
    .malloc = fail_alloc_malloc,
    .realloc = fail_alloc_realloc,
    .free = fail_alloc_free,
    /// \cond
};

#endif /* ifndef DSA_UTILS_ALLOCATOR_H */
