#ifndef DSA_UTILS_COMPARE_H
#define DSA_UTILS_COMPARE_H

// base type compare function generators

#define COMPARE_BTYPE_DCL(type, func_name) \
    int func_name(const void *a, const void *b)

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
