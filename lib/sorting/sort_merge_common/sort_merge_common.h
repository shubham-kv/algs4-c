#include <stddef.h>
#include "comparators.h"

#ifndef __merge_sort_common_h
#define __merge_sort_common_h

void merge(
    void *arr,
    void *aux,
    size_t width,
    int low,
    int mid,
    int high,
    ComparatorFn cmp
);

#endif // __merge_sort_common_h

