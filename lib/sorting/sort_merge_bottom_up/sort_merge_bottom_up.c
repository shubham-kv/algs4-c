#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_merge_bottom_up.h"
#include "arr_utils.h"

#define MIN(a, b) (a < b ? a : b)


void merge(
    void *arr,
    void *aux,
    size_t width,
    int low,
    int mid,
    int high,
    ComparatorFn cmp
) {
  memcpy(aux + low * width, arr + low * width, ((high - low) + 1) * width);

  const int iMin = low, iMax = mid;
  const int jMin = mid + 1, jMax = high;

  for (int i = iMin, j = jMin, k = low; k <= high; k++) {
    if (i > iMax) {
      memcpy(arr + k * width, aux + (j++) * width, width);
    } else if (j > jMax) {
      memcpy(arr + k * width, aux + (i++) * width, width);
    } else if (cmp(aux + j * width, aux + i * width) < 0) {
      memcpy(arr + k * width, aux + (j++) * width, width);
    } else {
      memcpy(arr + k * width, aux + (i++) * width, width);
    }
  }
}

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

