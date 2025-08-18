#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_heap.h"

static void swap(void *arr, size_t width, int i, int j);
static bool isSorted(void *arr, size_t width, int n, ComparatorFn cmp);


void sinkDown(void *arr, size_t width, int n, int p, ComparatorFn cmp) {
  for (
      int c = 2 * p + 1;
      c < n;
      p = c, c = 2 * p + 1
  ) {
    if (c + 1 < n && cmp(arr + c * width, arr + (c + 1) * width) < 0) {
      c += 1;
    }
    if (cmp(arr + p * width, arr + c * width) < 0) {
      swap(arr, width, p, c);
    } else {
      break;
    }
  }
}

void heapSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  for (int p = (n - 1 - 1) / 2; p >= 0; p--) {
    sinkDown(arr, width, n, p, cmp);
  }

  for (int s = n; s > 0; ) {
    swap(arr, width, 0, --s);
    sinkDown(arr, width, s, 0, cmp);
  }

  assert(isSorted(arr, width, n, cmp) == true);
}


static void swap(void *arr, size_t width, int i, int j) {
  char temp[width];
  memcpy(temp, arr + i * width, width);
  memcpy(arr + i * width, arr + j * width, width);
  memcpy(arr + j * width, temp, width);
}

static bool isSorted(void *arr, size_t width, int n, ComparatorFn cmp) {
  for (int i = 1; i < n; i++) {
    if (cmp(arr + (i - 1) * width, arr + i * width) > 0) {
      return false;
    }
  }
  return true;
}

