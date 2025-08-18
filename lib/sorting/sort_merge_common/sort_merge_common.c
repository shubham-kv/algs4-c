#include <memory.h>
#include <stdlib.h>
#include "sort_merge_common.h"

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

