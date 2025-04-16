#ifndef DSA_TYPES_ARRAY_H
#define DSA_TYPES_ARRAY_H

#include <stddef.h>

// array descriptor
struct array {
    void *buffer;
    size_t size;
    size_t memb_size;
};

static const struct array NULL_ARRAY = {
    .buffer = NULL,
    .size = 0,
    .memb_size = 0,
};

#endif /* ifndef DSA_TYPES_ARRAY_H */
