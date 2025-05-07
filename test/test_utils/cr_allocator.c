#include "dsa/test_utils/cr_allocator.h"

const struct allocator cr_allocator = {
    .malloc = cr_malloc,
    .realloc = cr_realloc,
    .free = cr_free,
};
