#include "dsa/core/types/allocator.h"

#include <stdlib.h>

const struct allocator stdlib_allocator = {
    .malloc = malloc,
    .realloc = realloc,
    .free = free,
};
