#ifndef MERGESORT
#define MERGESORT

#include <stddef.h>


typedef int (*comparator)(const void *, const void *);  

int mergeSort(void *, size_t, size_t, comparator);

#endif