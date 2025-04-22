#ifndef DSA_UTILS_MEMORY_H
#define DSA_UTILS_MEMORY_H

#include <stdbool.h>
#include <stddef.h>

// ith index of void pointer buffer by memb_size
#define buf_idx(buffer, i, memb_size) \
    ((void *)((unsigned char *)(buffer) + ((i) * (memb_size))))

// increment void pointer buffer by i by memb_size
#define buf_inc(buffer, i, memb_size) (buffer) = buf_idx(buffer, i, memb_size)

#endif /* ifndef DSA_UTILS_MEMORY_H */
