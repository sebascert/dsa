/**
 * \file dsa/utils/memory.h
 * \brief Memory utilities.
 */

#ifndef DSA_UTILS_MEMORY_H
#define DSA_UTILS_MEMORY_H

/**
 * \brief Declares a memcpy function from value to pointer, for the given type.
 *
 * \param type Type.
 * \param func_name Name of the declared function
 */
#define MEMCPY_TYPE_DCL(type, func_name) void func_name(type *dest, type src)

/**
 * \brief Defines a memcpy function from value to pointer, for the given type.
 *
 * Copies the given value to the given pointer. Useful for cases such as:
 * copying a literal or value struct to a non asignable struct.
 *
 * \param type Type.
 * \param func_name Name of the declared function
 */
#define MEMCPY_TYPE_DEF(type, func_name)  \
    MEMCPY_TYPE_DCL(type, func_name)      \
    {                                     \
        memcpy(dest, &src, sizeof(type)); \
    }

#endif /* ifndef DSA_UTILS_MEMORY_H */
