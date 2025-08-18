#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_insertion.h"
#include "arr_utils.h"

void insertionSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0; j--) {
      if (cmp(arr + j * width, arr + (j - 1) * width) < 0) {
        ArrUtils_Swap(arr, width, j, j - 1);
      } else {
        break;
      }
    }
  }
  assert(ArrUtils_IsSorted(arr, width, n, cmp) == true);
}

