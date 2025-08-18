#include <stddef.h>
#include "comparators.h"

#ifndef __quick_sort_h
#define __quick_sort_h

void quickSort(void *arr, size_t width, int n, ComparatorFn cmp);

#endif // __quick_sort_h  

