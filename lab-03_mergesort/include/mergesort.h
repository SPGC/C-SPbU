#ifndef MERGESORT
#define MERGESORT
#include <stddef.h>

typedef int (*comparator)(const void *, const void *);  

void merge(void *, void *, size_t, size_t, size_t, comparator, void *);

int mergeSort(void *, size_t, size_t, comparator);

void elementsCpy(void *, void *, size_t);

#endif