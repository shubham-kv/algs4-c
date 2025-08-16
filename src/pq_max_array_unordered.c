#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "pq_max_array_unordered.h"

#define KEY MaxPQ_Key
#define INITIAL_CAPACITY 4

void MaxPQ_Init(MaxPQ pq, ComparatorFn cmp) {
  pq->capacity = INITIAL_CAPACITY;
  pq->keys = calloc(pq->capacity, sizeof(KEY));
  pq->size = 0;
  pq->cmp = cmp;
}

void MaxPQ_Clear(MaxPQ pq) {
  free(pq->keys), (pq->keys = NULL);
  memset(pq, 0, sizeof(struct UnorderedArrayMaxPQ));
}

static void resizeKeys(MaxPQ pq, int newCapacity) {
  pq->keys = realloc(pq->keys, newCapacity * sizeof(KEY));
  pq->capacity = newCapacity;
}

void MaxPQ_Insert(MaxPQ pq, KEY key) {
  if (pq->size == pq->capacity) {
    resizeKeys(pq, pq->capacity * 2);
  }
  pq->keys[pq->size++] = key;
}

static int indexOfMax(MaxPQ pq) {
  if (MaxPQ_IsEmpty(pq)) {
    return -1;
  }

  int maxIndex = 0;

  for (int i = 1; i < pq->size; i++) {
    if (pq->cmp(pq->keys[maxIndex], pq->keys[i]) < 0) {
      maxIndex = i;
    }
  }

  return maxIndex;
}

inline KEY MaxPQ_GetMax(MaxPQ pq) {
  int maxIndex;
  return ((maxIndex = indexOfMax(pq)) < 0) ? NULL : pq->keys[maxIndex];
}

KEY MaxPQ_DelMax(MaxPQ pq) {
  const int maxIndex = indexOfMax(pq);

  if (maxIndex < 0) {
    return NULL;
  }

  KEY maxKey = pq->keys[maxIndex];
  pq->keys[maxIndex] = pq->keys[pq->size - 1];
  pq->keys[--pq->size] = NULL;

  if (pq->size <= pq->capacity / 4) {
    resizeKeys(pq, pq->capacity / 2);
  }

  return maxKey;
}

inline bool MaxPQ_IsEmpty(MaxPQ pq) {
  return MaxPQ_Size(pq) == 0;
}

inline int MaxPQ_Size(MaxPQ pq) {
  return pq->size;
}

#undef KEY
#undef INITIAL_CAPACITY

