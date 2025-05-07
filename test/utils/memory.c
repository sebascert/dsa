#include "dsa/utils/memory.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/theories.h>

#include <string.h>

#define suite utils_memory

// test the compare function func, of given type, by the given __VA_ARGS__
#define MEMCPY_THEORY_DEF(type, type_alias, ...)                  \
    static MEMCPY_TYPE_DEF(type, cpy_##type_alias);               \
    TheoryDataPoints(suite, cpy_##type_alias) = {                 \
        DataPoints(type, __VA_ARGS__),                            \
    };                                                            \
    Theory((type val), suite, cpy_##type_alias)                   \
    {                                                             \
        type dest;                                                \
        cpy_##type_alias(&dest, val);                             \
        cr_assert(eq(int, memcmp(&dest, &val, sizeof(type)), 0)); \
    }

MEMCPY_THEORY_DEF(int, int, -1, 0, 1, 42, -99)

MEMCPY_THEORY_DEF(float, float, -1.0f, 0.0f, 1.0f, 3.14159f, -2.718f)

MEMCPY_THEORY_DEF(double, double, -1.0, 0.0, 1.0, 2.99792458e8, -6.67430e-11)

MEMCPY_THEORY_DEF(char, char, -1, 0, 1, 'A', 'z', '0', '@')

MEMCPY_THEORY_DEF(short, short, -1, 0, 1, 1234, -4321)

MEMCPY_THEORY_DEF(long, long, -1, 0, 1, 987654321, -987654321)

MEMCPY_THEORY_DEF(long long, longlong, -1, 0, 1, 922337203685477LL,
                  -922337203685477LL)

MEMCPY_THEORY_DEF(unsigned int, uint, 0, 1, 99999, 424242)

MEMCPY_THEORY_DEF(unsigned char, uchar, 0, 1, 127, 200)

MEMCPY_THEORY_DEF(unsigned short, ushort, 0, 1, 32768, 12345)

MEMCPY_THEORY_DEF(unsigned long, ulong, 0, 1, 1000000000UL, 42424242UL)

MEMCPY_THEORY_DEF(unsigned long long, 0, 1, 1844674407370955ULL,
                  999999999999ULL)

#undef suite
