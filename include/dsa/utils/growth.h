/**
 * \file dsa/utils/growth.h
 * \brief Growth strategy samples.
 */

#ifndef DSA_UTILS_GROWTH_H
#define DSA_UTILS_GROWTH_H

#include <stddef.h>

/**
 * \brief Exponential growth strategy.
 *
 * \param n Current size.
 * \returns n * 2.
 */
static inline size_t exponential_growth(size_t n)
{
    return n * 2;
}

/**
 * \brief Exponential growth base for exponential_m_growth.
 */
#define EXPONENTIAL_BASE_M 3

/**
 * \brief Parametrized exponential growth strategy.
 *
 * \param n Current size.
 * \returns EXPONENTIAL_BASE_M * 2.
 */
static inline size_t exponential_m_growth(size_t n)
{
    return n * EXPONENTIAL_BASE_M;
}

/**
 * \brief Complete binary tree growth strategy.
 *
 * \param n Current size of a complete binary tree.
 * \returns n * 2 + 1.
 */
static inline size_t complete_bintree_growth(size_t n)
{
    return n * 2 + 1;
}

/**
 * \brief Approximates to next complete binary tree growth strategy.
 *
 * \param n Current size.
 * \returns n * 2 + 1.
 */
static inline size_t next_complete_bintree_growth(size_t n)
{
    size_t res = 1;
    while (n >= res) {
        res = res * 2 + 1;
    }
    return res;
}

#define DEFAULT_GROWTH exponential_growth

#endif /* ifndef DSA_UTILS_GROWTH_H */
