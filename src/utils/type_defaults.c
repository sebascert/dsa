#include "dsa/types/allocator.h"
#include "dsa/types/array.h"

const struct allocator stdlib_allocator = {
    .malloc = malloc,
    .realloc = realloc,
    .free = free,
};

const struct array NULL_ARRAY = {
    .buffer = NULL,
    .size = 0,
    .memb_size = 0,
};
