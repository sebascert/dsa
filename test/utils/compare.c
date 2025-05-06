#include "dsa/utils/compare.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#include <limits.h>

#define suite utils_compare

// test the compare function of given type func, by the given __VA_ARGS__
#define COMPARE_THEORY_DEF(type, func, ...)                           \
    TheoryDataPoints(suite, func) = {                                 \
        DataPoints(type, __VA_ARGS__),                                \
        DataPoints(type, __VA_ARGS__),                                \
    };                                                                \
                                                                      \
    Theory((type arg0, type arg1), suite, func)                       \
    {                                                                 \
        /*test against this implementation*/                          \
        int expected = (arg0 == arg1) ? 0 : ((arg0 > arg1) ? 1 : -1); \
        cr_assert(eq(int, func(&arg0, &arg1), expected));             \
        cr_assert(eq(int, func(&arg1, &arg0), -expected));            \
    }

static COMPARE_BTYPE_DEF(int, compare_int_theory);
static COMPARE_BTYPE_DEF(float, compare_float_theory);
static COMPARE_BTYPE_DEF(double, compare_double_theory);
static COMPARE_BTYPE_DEF(char, compare_char_theory);
static COMPARE_BTYPE_DEF(short, compare_short_theory);
static COMPARE_BTYPE_DEF(long, compare_long_theory);
static COMPARE_BTYPE_DEF(long long, compare_longlong_theory);
static COMPARE_BTYPE_DEF(unsigned int, compare_uint_theory);
static COMPARE_BTYPE_DEF(unsigned char, compare_uchar_theory);
static COMPARE_BTYPE_DEF(unsigned short, compare_ushort_theory);
static COMPARE_BTYPE_DEF(unsigned long, compare_ulong_theory);
static COMPARE_BTYPE_DEF(unsigned long long, compare_ulonglong_theory);

COMPARE_THEORY_DEF(int, compare_int_theory, INT_MAX, INT_MIN, -1, 0, 1, 42, -99)

COMPARE_THEORY_DEF(float, compare_float_theory, FLT_MAX, -FLT_MAX, FLT_MIN,
                   -FLT_MIN, -1.0f, 0.0f, 1.0f, 3.14159f, -2.718f)

COMPARE_THEORY_DEF(double, compare_double_theory, DBL_MAX, -DBL_MAX, DBL_MIN,
                   -DBL_MIN, -1.0, 0.0, 1.0, 2.99792458e8, -6.67430e-11)

COMPARE_THEORY_DEF(char, compare_char_theory, CHAR_MAX, CHAR_MIN, -1, 0, 1, 'A',
                   'z', '0', '@')

COMPARE_THEORY_DEF(short, compare_short_theory, SHRT_MAX, SHRT_MIN, -1, 0, 1,
                   1234, -4321)

COMPARE_THEORY_DEF(long, compare_long_theory, LONG_MAX, LONG_MIN, -1, 0, 1,
                   987654321, -987654321)

COMPARE_THEORY_DEF(long long, compare_longlong_theory, LLONG_MAX, LLONG_MIN, -1,
                   0, 1, 922337203685477LL, -922337203685477LL)

COMPARE_THEORY_DEF(unsigned int, compare_uint_theory, UINT_MAX, 0, 1, 99999,
                   424242)

COMPARE_THEORY_DEF(unsigned char, compare_uchar_theory, UCHAR_MAX, 0, 1, 127,
                   200)

COMPARE_THEORY_DEF(unsigned short, compare_ushort_theory, USHRT_MAX, 0, 1,
                   32768, 12345)

COMPARE_THEORY_DEF(unsigned long, compare_ulong_theory, ULONG_MAX, 0, 1,
                   1000000000UL, 42424242UL)

COMPARE_THEORY_DEF(unsigned long long, compare_ulonglong_theory, ULLONG_MAX, 0,
                   1, 1844674407370955ULL, 999999999999ULL)

#undef suite
