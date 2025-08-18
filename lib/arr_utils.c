#include <memory.h>
#include <stdlib.h>
#include "arr_utils.h"

void ArrUtils_Swap(void *arr, size_t width, size_t i, size_t j) {
  char temp[width];
  memcpy(temp, arr + i * width, width);
  memcpy(arr + i * width, arr + j * width, width);
  memcpy(arr + j * width, temp, width);
}

bool ArrUtils_IsSorted(void *arr, size_t width, size_t n, ComparatorFn cmp) {
  for (size_t i = 1; i < n; i++) {
    if (cmp(arr + (i - 1) * width, arr + i * width) > 0) {
      return false;
    }
  }
  return true;
}

