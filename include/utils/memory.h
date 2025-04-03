#ifndef DSA_UTILS_MEMORY_H
#define DSA_UTILS_MEMORY_H

#include <stddef.h>

// ith index of void pointer buffer by memb_size
#define buf_idx(buffer, i, memb_size) \
    ((void *)((unsigned char *)(buffer) + ((i) * (memb_size))))

// increment void pointer buffer by i by memb_size
#define buf_inc(buffer, i, memb_size) (buffer) = buf_idx(buffer, i, memb_size)

// swap elements in a buffer by indexes a and b
// no memory boundaries are checked
void swap_buffer_elems(void *buffer, size_t memb_size, size_t a, size_t b);

#endif /* ifndef DSA_UTILS_MEMORY_H */
