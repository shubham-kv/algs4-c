#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_shell.h"
#include "arr_utils.h"

void shellSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  int h;
  for (h = 1; h < n / 3; h = 3 * h + 1) { }

  for (; h >= 1; h /= 3) {
    for (int i = h; i < n; i++) {
      for (int j = i; j - h >= 0; j -= h) {
        if (cmp(arr + j * width, arr + (j - h) * width) < 0) {
          ArrUtils_Swap(arr, width, j, j - h);
        } else {
          break;
        }
      }
    }
  }
  assert(ArrUtils_IsSorted(arr, width, n, cmp) == true);
}

