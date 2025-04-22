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
 * \param n Current size.
 * \returns n * 2 + 1.
 */
static inline size_t complete_binary_tree_growth(size_t n)
{
    return n * 2 + 1;
}

#endif /* ifndef DSA_UTILS_GROWTH_H */
