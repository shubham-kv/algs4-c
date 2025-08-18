#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort_shell.h"

static void swap(void *arr, size_t width, int i, int j);
static bool isSorted(void *arr, size_t width, size_t n, ComparatorFn cmp);

void shellSort(void *arr, size_t width, int n, ComparatorFn cmp) {
  int h;
  for (h = 1; h < n / 3; h = 3 * h + 1) { }

  for (; h >= 1; h /= 3) {
    for (int i = h; i < n; i++) {
      for (int j = i; j - h >= 0; j -= h) {
        if (cmp(arr + j * width, arr + (j - h) * width) < 0) {
          swap(arr, width, j, j - h);
        } else {
          break;
        }
      }
    }
  }

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


