#include "growth.h"

size_t cuadratic_growth(size_t n) {
    return n * 2;
}

size_t polynomic_m_growth(size_t n) {
    return n * POLYNOMIC_M_DEGREE;
}

size_t complete_binary_tree_growth(size_t n) {
    return 1 + n * 2;
}
