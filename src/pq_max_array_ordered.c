#include <memory.h>
#include <stdlib.h>
#include "pq_max_array_ordered.h"

#define KEY MaxPQ_Key
#define INITIAL_CAPACITY 4

void MaxPQ_Init(MaxPQ pq, ComparatorFn keysCmp) {
  pq->capacity = INITIAL_CAPACITY;
  pq->keys = calloc(pq->capacity, sizeof(KEY));
  pq->size = 0;
  pq->cmp = keysCmp;
}

void MaxPQ_Clear(MaxPQ pq) {
  free(pq->keys), (pq->keys = NULL);
  memset(pq, 0, sizeof(struct OrderedArrayMaxPQ));
}

static void resizeKeys(MaxPQ pq, int newCapacity) {
  pq->keys = realloc(pq->keys, newCapacity * sizeof(KEY));
  pq->capacity = newCapacity;
}

void MaxPQ_Insert(MaxPQ pq, KEY key) {
  if (pq->size == pq->capacity) {
    resizeKeys(pq, pq->capacity * 2);
  }

  int i = 0;

  for (
      i = 0;
      i < pq->size && pq->cmp(pq->keys[i], key) < 0;
      i++
  ) {
  }

  for (int j = pq->size; j - 1 >= i; j--) {
    pq->keys[j] = pq->keys[j - 1];
  }
  pq->keys[i] = key;
  pq->size++;
}

inline KEY MaxPQ_GetMax(MaxPQ pq) {
  return MaxPQ_IsEmpty(pq) ? NULL : pq->keys[pq->size - 1];
}

KEY MaxPQ_DelMax(MaxPQ pq) {
  if (MaxPQ_IsEmpty(pq)) {
    return NULL;
  }

  KEY max = pq->keys[pq->size - 1];
  pq->keys[--pq->size] = NULL;

  if (pq->size <= pq->capacity / 4) {
    resizeKeys(pq, pq->capacity / 2);
  }

  return max;
}

inline bool MaxPQ_IsEmpty(MaxPQ pq) {
  return MaxPQ_Size(pq) == 0;
}

inline int MaxPQ_Size(MaxPQ pq) {
  return pq->size;
}

#undef KEY
#undef INITIAL_CAPACITY

