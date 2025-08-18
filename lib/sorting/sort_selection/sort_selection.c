#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_selection.h"
#include "arr_utils.h"

void selectionSort(void *arr, size_t width, size_t n, ComparatorFn cmp) {
  for (size_t i = 0; i < n; i++) {
    size_t minIndex = i;

    for (size_t j = i + 1; j < n; j++) {
      if (cmp(arr + width * j, arr + width * minIndex) < 0) {
        minIndex = j;
      }
    }

    if (minIndex == i) {
      continue;
    }
    ArrUtils_Swap(arr, width, i, minIndex);
  }

  assert(ArrUtils_IsSorted(arr, width, n, cmp) == true);
}

