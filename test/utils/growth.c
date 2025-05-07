#include "dsa/utils/growth.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#define suite utils_growth

// struct size must remain less than sizeof(uint64_t)
struct growth_tc {
    unsigned int curr;
    unsigned int next;
};

TheoryDataPoints(suite, exponential_growth) = {
    DataPoints(struct growth_tc, {0, 0}, {1, 2}, {2, 4}, {5, 10}, {8, 16}),
};
Theory((struct growth_tc tc), suite, exponential_growth)
{
    cr_assert(eq(sz, exponential_growth(tc.curr), tc.next));
}

TheoryDataPoints(suite, exponential_m_growth) = {
    DataPoints(struct growth_tc, {0, 0}, {1, 1}, {2, 2}, {5, 5}, {8, 8}),
};
Theory((struct growth_tc tc), suite, exponential_m_growth)
{
    cr_assert(
        eq(sz, exponential_m_growth(tc.curr), tc.curr * EXPONENTIAL_BASE_M));
}

TheoryDataPoints(suite, complete_bintree_growth) = {
    DataPoints(struct growth_tc, {0, 1}, {1, 3}, {2, 5}, {5, 11}, {8, 17}),
};
Theory((struct growth_tc tc), suite, complete_bintree_growth)
{
    cr_assert(eq(sz, complete_bintree_growth(tc.curr), tc.next));
}

TheoryDataPoints(suite, next_complete_bintree_growth) = {
    DataPoints(struct growth_tc, {0, 1}, {1, 3}, {2, 3}, {4, 7}, {8, 15}),
};
Theory((struct growth_tc tc), suite, next_complete_bintree_growth)
{
    cr_assert(eq(sz, next_complete_bintree_growth(tc.curr), tc.next));
}

#undef suite
