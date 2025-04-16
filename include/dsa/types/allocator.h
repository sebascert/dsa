#ifndef DSA_TYPES_ALLOCATOR_H
#define DSA_TYPES_ALLOCATOR_H

#include <memory.h>
#include <stdlib.h>

typedef void* (*Malloc)(size_t);
typedef void* (*Realloc)(void*, size_t);
typedef void (*Free)(void*);

// container for the functions of an allocator
struct allocator {
    Malloc malloc;
    Realloc realloc;
    Free free;
};

extern const struct allocator stdlib_allocator;

#endif /* ifndef DSA_TYPES_ALLOCATOR_H */
