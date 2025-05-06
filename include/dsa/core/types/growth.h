/**
 * \file dsa/core/types/growth.h
 * \brief Growth strategy type.
 */

#ifndef DSA_CORE_TYPES_GROWTH_H
#define DSA_CORE_TYPES_GROWTH_H

#include <stddef.h>

/**
 * \brief Growth strategy function pointer.
 *
 * Provides an interface for a growth strategy where dynamic growth is needed
 * and must be specified via function pointer.
 */
typedef size_t (*Growth)(size_t);

#endif /* ifndef DSA_CORE_TYPES_GROWTH_H */
