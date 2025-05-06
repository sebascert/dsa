/**
 * \file dsa/core/utils/memory.h
 * \brief Memory utilities.
 */

#ifndef DSA_CORE_UTILS_MEMORY_H
#define DSA_CORE_UTILS_MEMORY_H

#include <stdbool.h>
#include <stddef.h>

/**
 * \brief Index element of buffer of memb_size size elements.
 *
 * \param buffer Pointer treated as raw memory.
 * \param idx Index.
 * \param memb_size Buffer member size.
 */
#define buf_idx(buffer, idx, memb_size) \
    ((void *)((unsigned char *)(buffer) + ((idx) * (memb_size))))

/**
 * \brief Increment by i elements lvalue buffer of memb_size size elements.
 *
 * \param buffer Pointer treated as raw memory and lvalue.
 * \param i Increment.
 * \param memb_size Buffer member size.
 */
#define buf_inc(buffer, i, memb_size) (buffer) = buf_idx(buffer, i, memb_size)

#endif /* ifndef DSA_CORE_UTILS_MEMORY_H */
