#include <stddef.h>
#include "comparators.h"

#ifndef __heap_sort_h
#define __heap_sort_h

void heapSort(void *arr, size_t width, int n, ComparatorFn cmp);

#endif // __heap_sort_h

