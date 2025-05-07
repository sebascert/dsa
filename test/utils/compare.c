#include "dsa/utils/compare.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#include <limits.h>

#define suite utils_compare

// test the compare function func, of given type, by the given __VA_ARGS__
#define COMPARE_THEORY_DEF(type, type_alias, ...)                          \
    static COMPARE_BTYPE_DEF(type, compare_##type_alias);                  \
    TheoryDataPoints(suite, compare_##type_alias) = {                      \
        DataPoints(type, __VA_ARGS__),                                     \
        DataPoints(type, __VA_ARGS__),                                     \
    };                                                                     \
    Theory((type arg0, type arg1), suite, compare_##type_alias)            \
    {                                                                      \
        /*test against this implementation*/                               \
        int expected = (arg0 == arg1) ? 0 : ((arg0 > arg1) ? 1 : -1);      \
        cr_assert(eq(int, compare_##type_alias(&arg0, &arg1), expected));  \
        cr_assert(eq(int, compare_##type_alias(&arg1, &arg0), -expected)); \
    }

COMPARE_THEORY_DEF(int, int, INT_MAX, INT_MIN, -1, 0, 1, 42, -99)

COMPARE_THEORY_DEF(float, float, FLT_MAX, -FLT_MAX, FLT_MIN, -FLT_MIN, -1.0f,
                   0.0f, 1.0f, 3.14159f, -2.718f)

COMPARE_THEORY_DEF(double, double, DBL_MAX, -DBL_MAX, DBL_MIN, -DBL_MIN, -1.0,
                   0.0, 1.0, 2.99792458e8, -6.67430e-11)

COMPARE_THEORY_DEF(char, char, CHAR_MAX, CHAR_MIN, -1, 0, 1, 'A', 'z', '0', '@')

COMPARE_THEORY_DEF(short, short, SHRT_MAX, SHRT_MIN, -1, 0, 1, 1234, -4321)

COMPARE_THEORY_DEF(long, long, LONG_MAX, LONG_MIN, -1, 0, 1, 987654321,
                   -987654321)

COMPARE_THEORY_DEF(long long, longlong, LLONG_MAX, LLONG_MIN, -1, 0, 1,
                   922337203685477LL, -922337203685477LL)

COMPARE_THEORY_DEF(unsigned int, uint, UINT_MAX, 0, 1, 99999, 424242)

COMPARE_THEORY_DEF(unsigned char, uchar, UCHAR_MAX, 0, 1, 127, 200)

COMPARE_THEORY_DEF(unsigned short, ushort, USHRT_MAX, 0, 1, 32768, 12345)

COMPARE_THEORY_DEF(unsigned long, ulong, ULONG_MAX, 0, 1, 1000000000UL,
                   42424242UL)

COMPARE_THEORY_DEF(unsigned long long, ulonglong, ULLONG_MAX, 0, 1,
                   1844674407370955ULL, 999999999999ULL)

#undef suite
