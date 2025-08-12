#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_selection.h"

static void swap(void *arr, size_t width, size_t i, size_t j);
static bool isSorted(void *arr, size_t width, size_t n, ComparatorFn cmp);

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

    swap(arr, width, i, minIndex);
  }

  assert(isSorted(arr, width, n, cmp) == true);
}

static void swap(void *arr, size_t width, size_t i, size_t j) {
  char temp[width];
  memcpy(temp, arr + i * width, width);
  memcpy(arr + i * width, arr + j * width, width);
  memcpy(arr + j * width, temp, width);
}

static bool isSorted(void *arr, size_t width, size_t n, ComparatorFn cmp) {
  for (size_t i = 1; i < n; i++) {
    if (cmp(arr + (i - 1) * width, arr + i * width) > 0) {
      return false;
    }
  }
  return true;
}

