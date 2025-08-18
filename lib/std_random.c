#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "std_random.h"

static void swap(void *arr, size_t width, int i, int j);

void StdRandom_seed(uint32_t seed) {
  srand(seed);
}

/** Random integer in the range `[min, max]` */
int StdRandom_uniformInt(int min, int max) {
  return min + rand() % (max - min + 1);
}

/** Random double in the range `[0.0, 1.0)` */
double StdRandom_uniform() {
  return (double) (rand() / (RAND_MAX + 1.0));
}

/** Random double in the range `[min, max)` */
double StdRandom_uniformDouble(double min, double max) {
  return min + StdRandom_uniform() * (max - min);
}

/** Fisher-Yates shuffle for the given array */
void StdRandom_shuffle(void *arr, size_t width, size_t n) {
  for (size_t i = 1; i < n; i++) {
    size_t r = StdRandom_uniformInt(0, i);

    if (i != r) {
      swap(arr, width, i, r);
    }
  }
}

static void swap(void *arr, size_t width, int i, int j) {
  char temp[width];
  memcpy(temp, arr + i * width, width);
  memcpy(arr + i * width, arr + j * width, width);
  memcpy(arr + j * width, temp, width);
}

