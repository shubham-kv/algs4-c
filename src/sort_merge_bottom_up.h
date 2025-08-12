#include <stddef.h>
#include "comparators.h"

#ifndef __bottom_up_merge_sort_h
#define __bottom_up_merge_sort_h

void bottomUpMergeSort(void *arr, size_t width, int n, ComparatorFn cmp);

#endif // __bottom_up_merge_sort_h

