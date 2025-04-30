#include "dsa/utils/growth.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>

#define suite utils_growth

struct growth_tc {
    size_t size;
    size_t exp;
    size_t exp_m;
    size_t bintree;
    size_t next_bintree;
};

ParameterizedTestParameters(suite, strategies)
{
    static struct growth_tc params[] = {
        {0, 0, 0, 1, 1},    {1, 2, 3, 3, 3},      {2, 4, 6, 5, 3},
        {5, 10, 15, 11, 7}, {10, 20, 30, 21, 15}, {15, 30, 45, 31, 31},
    };
    return cr_make_param_array(struct growth_tc, params,
                               sizeof(params) / sizeof(struct growth_tc));
}
ParameterizedTest(struct growth_tc* tc, suite, strategies)
{
    cr_assert(eq(sz, exponential_growth(tc->size), tc->exp));
    cr_assert(eq(sz, exponential_m_growth(tc->size), tc->exp_m));
    cr_assert(eq(sz, complete_bintree_growth(tc->size), tc->bintree));
    cr_assert(eq(sz, next_complete_bintree_growth(tc->size), tc->next_bintree));
}

#undef suite
