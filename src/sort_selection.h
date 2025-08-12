#include <stddef.h>
#include "comparators.h"

#ifndef __selection_sort_h
#define __selection_sort_h

void selectionSort(void *arr, size_t width, size_t n, ComparatorFn cmp);

#endif // __selection_sort_h

