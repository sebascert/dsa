#include "growth.h"

size_t exponential_growth(size_t n) {
    return n * 2;
}

size_t exponential_m_growth(size_t n) {
    return n * EXPONENTIAL_BASE_M;
}

size_t complete_binary_tree_growth(size_t n) {
    return 1 + n * 2;
}
