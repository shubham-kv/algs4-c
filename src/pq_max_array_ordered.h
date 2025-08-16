#include <stdbool.h>
#include "comparators.h"

#ifndef __ordered_array_max_pq
#define __ordered_array_max_pq

typedef const void *MaxPQ_Key;

struct OrderedArrayMaxPQ {
  MaxPQ_Key *keys;
  int size;
  int capacity;
  ComparatorFn cmp;
};
typedef struct OrderedArrayMaxPQ *MaxPQ;

#define KEY MaxPQ_Key

void MaxPQ_Init(MaxPQ pq, ComparatorFn keysCmp);
void MaxPQ_Clear(MaxPQ pq);
void MaxPQ_Insert(MaxPQ pq, KEY key);
 KEY MaxPQ_GetMax(MaxPQ pq);
 KEY MaxPQ_DelMax(MaxPQ pq);
bool MaxPQ_IsEmpty(MaxPQ pq);
 int MaxPQ_Size(MaxPQ pq);

#undef KEY

#endif // __ordered_array_max_pq

