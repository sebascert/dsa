#ifndef DSA_TYPES_COMPARE_H
#define DSA_TYPES_COMPARE_H

// a < b <-> int < 0
// a > b <-> int > 0
// a == b <-> int == 0
typedef int (*Compare)(const void *, const void *);

#endif /* ifndef DSA_TYPES_COMPARE_H */
