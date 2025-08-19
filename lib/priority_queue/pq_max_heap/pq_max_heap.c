#include <memory.h>
#include <stdlib.h>
#include "pq_max_heap.h"

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
  memset(pq, 0, sizeof(struct HeapMaxPQ));
}

static void resizeKeys(MaxPQ pq, int newCapacity) {
  pq->keys = realloc(pq->keys, newCapacity * sizeof(struct HeapMaxPQ));
  pq->capacity = newCapacity;
}

static void swapKeys(MaxPQ pq, int i, int j) {
  KEY key = pq->keys[i];
  pq->keys[i] = pq->keys[j];
  pq->keys[j] = key;
}

static void swimUp(MaxPQ pq, int c) {
  for (
      int p = c / 2;
      p >= 1 && pq->cmp(pq->keys[p], pq->keys[c]) < 0;
      c = p, p = c / 2
  ) {
    swapKeys(pq, p, c);
  }
}

static void sinkDown(MaxPQ pq, int p) {
  for (
      int c = 2 * p;
      c <= pq->size;
      p = c, c = 2 * p
  ) {
    if (c + 1 <= pq->size && pq->cmp(pq->keys[c], pq->keys[c + 1]) < 0) {
      c += 1;
    }
    if (pq->cmp(pq->keys[p], pq->keys[c]) < 0) {
      swapKeys(pq, p, c);
    } else {
      break;
    }
  }
}

void MaxPQ_Insert(MaxPQ pq, KEY key) {
  if ((pq->size + 1) >= pq->capacity) {
    resizeKeys(pq, pq->capacity * 2);
  }

  pq->keys[++pq->size] = key;
  swimUp(pq, pq->size);
}

inline KEY MaxPQ_GetMax(MaxPQ pq) {
  return MaxPQ_IsEmpty(pq) ? NULL : pq->keys[1];
}

KEY MaxPQ_DelMax(MaxPQ pq) {
  if (MaxPQ_IsEmpty(pq)) {
    return NULL;
  }

  KEY max = pq->keys[1];
  pq->keys[1] = pq->keys[pq->size];
  pq->keys[pq->size--] = NULL;
  sinkDown(pq, 1);

  if (pq->size > 0 && pq->size <= pq->capacity / 4) {
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

