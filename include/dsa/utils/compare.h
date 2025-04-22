/**
 * \file dsa/utils/compare.h
 * \brief Comparison function generation.
 */

#ifndef DSA_UTILS_COMPARE_H
#define DSA_UTILS_COMPARE_H

/**
 * \brief Declare a comparison for the given base type.
 *
 * \param type Compared base type.
 * \param func_name Name of the declared function
 */
#define COMPARE_BTYPE_DCL(type, func_name) \
    int func_name(const void *a, const void *b)

/**
 * \brief Defines a comparison for the given base type.
 *
 * \param type Compared base type.
 * \param func_name Name of the declared function
 */
#define COMPARE_BTYPE_DEF(type, func_name) \
    COMPARE_BTYPE_DCL(type, func_name)     \
    {                                      \
        const type arg1 = *((type *)a);    \
        const type arg2 = *((type *)b);    \
        if (arg1 == arg2)                  \
            return 0;                      \
        return (arg1 > arg2) ? 1 : -1;     \
    }

#endif /* ifndef DSA_UTILS_COMPARE_H */
