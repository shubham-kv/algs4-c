#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "sort_quick.h"
#include "sort_insertion.h"
#include "std_random.h"

#define CUT_OFF 5

static void swap(void *arr, size_t width, int i, int j);
static bool isSorted(void *arr, size_t width, size_t n, ComparatorFn cmp);

int partition(
    void *arr,
    size_t width,
    const int low,
    const int high,
    ComparatorFn cmp
) {
  const int p = low;
  int i = low, j = high + 1;
  const void *pItem = arr + p * width;

  while (true) {
    while (
        cmp(arr + (++i) * width, pItem) < 0 &&
        (i < high)
    ) { }

    while (
        cmp(pItem, arr + (--j) * width) < 0 &&
        (j > low)
    ) { }

    if (i >= j) {
      break;
    }

    swap(arr, width, i, j);
  }

  swap(arr, width, p, j);
  return j;
}

void quickSortRecursive(
    void *arr,
    size_t width,
    int low,
    int high,
    ComparatorFn cmp
) {
  if (!(low < high)) {
    return;
  }

  const int n = (high - low) + 1;

  if (n <= CUT_OFF) {
    insertionSort(arr + low * width, width, n, cmp);
    return;
  }

  int p = partition(arr, width, low, high, cmp);
  quickSortRecursive(arr, width, low, p - 1, cmp);
  quickSortRecursive(arr, width, p + 1, high, cmp);
}

void quickSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  StdRandom_seed(time(NULL));
  StdRandom_shuffle(arr, width, n);
  quickSortRecursive(arr, width, 0, n - 1, cmp);

  assert(isSorted(arr, width, n, cmp) == true);
}


static void swap(void *arr, size_t width, int i, int j) {
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

#undef CUT_OFF

