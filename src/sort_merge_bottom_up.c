#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_merge_top_down.h"
#include "sort_merge_bottom_up.h"

#define MIN(a, b) (a < b ? a : b)

static bool isSorted(void *arr, size_t width, size_t n, ComparatorFn cmp);


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
  assert(isSorted(arr, width, n, cmp) == true);
}


static bool isSorted(void *arr, size_t width, size_t n, ComparatorFn cmp) {
  for (size_t i = 1; i < n; i++) {
    if (cmp(arr + (i - 1) * width, arr + i * width) > 0) {
      return false;
    }
  }
  return true;
}

#undef MIN

