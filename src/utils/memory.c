#include "memory.h"

#include <stdio.h>
#include <string.h>

#define swap_size 64

void swap_buffer_elems(void* buffer, size_t memb_size, size_t a, size_t b) {
    if (a == b || memb_size == 0) return;

    unsigned char buf[swap_size];

    unsigned char* p1 = buf_idx(buffer, a, memb_size);
    unsigned char* p2 = buf_idx(buffer, b, memb_size);

    while (memb_size > swap_size) {
        memcpy(buf, p1, swap_size);
        memcpy(p1, p2, swap_size);
        memcpy(p2, buf, swap_size);

        memb_size -= swap_size;
        p1 += swap_size;
        p2 += swap_size;
    }

    memcpy(buf, p1, memb_size);
    memcpy(p1, p2, memb_size);
    memcpy(p2, buf, memb_size);
}
