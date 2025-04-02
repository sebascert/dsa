#ifndef DSA_ALLOCATOR_H
#define DSA_ALLOCATOR_H

#include <stddef.h>

typedef void* (*Malloc)(size_t);
typedef void* (*Realloc)(void*, size_t);
typedef void (*Free)(void*);

// container for the functions of an allocator
struct allocator {
    Malloc malloc;
    Realloc realloc;
    Free free;
};

#define STDLIB_ALLOCATOR ((struct allocator){malloc, realloc, free})

#endif /* ifndef DSA_ALLOCATOR_H */
