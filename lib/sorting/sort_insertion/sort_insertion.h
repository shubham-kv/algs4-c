#include <stddef.h>
#include "comparators.h"

#ifndef __insertion_sort_h
#define __insertion_sort_h

void insertionSort(void *arr, size_t width, int n, ComparatorFn cmp);

#endif // __insertion_sort_h

