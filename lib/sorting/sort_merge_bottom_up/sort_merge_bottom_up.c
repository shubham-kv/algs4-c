#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sort_merge_common.h"
#include "sort_merge_bottom_up.h"
#include "arr_utils.h"

#define MIN(a, b) (a < b ? a : b)

void bottomUpMergeSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  void *aux = calloc(n, width);

  for (int l = 1; l < n; l *= 2) {
    for (int low = 0; low + l < n; low += 2 * l) {
      const int mid = low + l - 1;
      const int high = MIN(low + 2 * l - 1, n - 1);

      if (cmp(arr + (mid + 1) * width, arr + mid * width) < 0) {
        merge(arr, aux, width, low, mid, high, cmp);
      }
    }
  }

  free(aux), (aux = NULL);
  assert(ArrUtils_IsSorted(arr, width, n, cmp) == true);
}

#undef MIN

