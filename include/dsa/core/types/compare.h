/**
 * \file dsa/core/types/compare.h
 * \brief Compare strategy type.
 */

#ifndef DSA_CORE_TYPES_COMPARE_H
#define DSA_CORE_TYPES_COMPARE_H

/**
 * \brief Compare strategy function pointer.
 *
 * Provides an interface for a comparison strategy between generic types.
 * \retval <0 When a < b
 * \retval >0 When a > b
 * \retval =0 When a = b
 */
typedef int (*Compare)(const void *, const void *);

#endif /* ifndef DSA_CORE_TYPES_COMPARE_H */
