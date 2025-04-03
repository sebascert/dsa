#ifndef DSA_UTILS_GROWTH_H
#define DSA_UTILS_GROWTH_H

#include <stddef.h>

// growth strategy
typedef size_t (*Growth)(size_t);

size_t cuadratic_growth(size_t n);

#define POLYNOMIC_M_DEGREE 3
size_t polynomic_m_growth(size_t n);

size_t complete_binary_tree_growth(size_t n);

#endif /* ifndef DSA_UTILS_GROWTH_H */
