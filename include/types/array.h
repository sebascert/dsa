#ifndef DSA_TYPES_ARRAY_H
#define DSA_TYPES_ARRAY_H

#include <stddef.h>

// array descriptor
struct array {
    void *buffer;
    size_t size;
    size_t memb_size;
};

#define NULL_ARRAY ((struct array){NULL, 0, 0})

#endif /* ifndef DSA_TYPES_ARRAY_H */
