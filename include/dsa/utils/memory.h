/**
 * \file dsa/utils/memory.h
 * \brief Memory utilities.
 */

#ifndef DSA_UTILS_MEMORY_H
#define DSA_UTILS_MEMORY_H

/**
 * \brief Declares a memcpy function from value to pointer, for the given type.
 *
 * \param type_alias Alias of the given type.
 * \param type Type.
 */
#define MEMCPY_TYPE_DCL(alias_name, type) \
    void cpy_##alias_name(type *dest, type src)

/**
 * \brief Defines a memcpy function from value to pointer, for the given type.
 *
 * Copies the given value to the given pointer. Usefull for cases such as:
 * copying a literal or value struct to a non asignable struct.
 *
 * \param type_alias Alias of the given type.
 * \param type Type.
 */
#define MEMCPY_TYPE_DEF(alias_name, type) \
    MEMCPY_TYPE_DCL(alias_name, type)     \
    {                                     \
        memcpy(dest, &src, sizeof(type)); \
    }

#endif /* ifndef DSA_UTILS_MEMORY_H */
