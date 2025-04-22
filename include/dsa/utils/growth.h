#ifndef DSA_UTILS_GROWTH_H
#define DSA_UTILS_GROWTH_H

#include <stddef.h>

static inline size_t exponential_growth(size_t n)
{
    return n * 2;
}

#define EXPONENTIAL_BASE_M 3
static inline size_t exponential_m_growth(size_t n)
{
    return n * EXPONENTIAL_BASE_M;
}

static inline size_t complete_binary_tree_growth(size_t n)
{
    return n * 2 + 1;
}

#endif /* ifndef DSA_UTILS_GROWTH_H */
