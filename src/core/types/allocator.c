#include "dsa/core/types/allocator.h"

const struct allocator stdlib_allocator = {
    .malloc = malloc,
    .realloc = realloc,
    .free = free,
};
