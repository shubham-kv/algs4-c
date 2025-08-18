#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sort_merge_top_down.h"
#include "sort_insertion.h"
#include "arr_utils.h"

#define CUT_OFF 6

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

static void topDownMergeSortRecursive(
    void *arr,
    void *aux,
    size_t width,
    int low,
    int high,
    ComparatorFn cmp
) {
  if (!(low < high)) {
    return;
  }

  const int n = (high - low) + 1;
  const int mid = (low + high) / 2;

  if (n <= CUT_OFF) {
    insertionSort(arr + low * width, width, n, cmp);
    return;
  }

  topDownMergeSortRecursive(arr, aux, width, low, mid, cmp);
  topDownMergeSortRecursive(arr, aux, width, mid + 1, high, cmp);

  if (cmp(arr + (mid + 1) * width, arr + mid * width) < 0) {
    merge(arr, aux, width, low, mid, high, cmp);
  }
}

void topDownMergeSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  void *aux = calloc(n, width);
  topDownMergeSortRecursive(arr, aux, width, 0, n - 1, cmp);
  free(aux), (aux = NULL);

  assert(ArrUtils_IsSorted(arr, width, n, cmp) == true);
}

#undef CUT_OFF

