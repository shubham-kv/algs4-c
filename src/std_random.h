#include <stdlib.h>

#if !defined(__std_random_h)
#define __std_random_h

void StdRandom_seed(uint32_t seed);

/** Random integer in the range `[min, max]` */
int StdRandom_uniformInt(int min, int max);

/** Random double in the range `[0.0, 1.0)` */
double StdRandom_uniform();

/** Random double in the range `[min, max)` */
double StdRandom_uniformDouble(double min, double max);

/** Fisher-Yates shuffle for the given array */
void StdRandom_shuffle(void *arr, size_t width, size_t n);

#endif // __std_random_h

