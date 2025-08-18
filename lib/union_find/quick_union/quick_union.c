#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include "quick_union.h"

void QuickUnion_Init(UF uf, uint32_t n) {
  assert(uf);
  uf->capacity = n;
  uf->entries = calloc(uf->capacity, sizeof(int));
  uf->countOfComponents = n;

  for (int i = 0; i < uf->capacity; i++) {
    uf->entries[i] = i;
  }
}

void QuickUnion_Clear(UF uf) {
  assert(uf);
  free(uf->entries), (uf->entries = NULL);
  memset(uf, 0, sizeof(struct QuickUnion));
}

void QuickUnion_Union(UF uf, int p, int q) {
  assert(uf);
  assert(0 <= p && p < uf->capacity);
  assert(0 <= q && q < uf->capacity);

  int rootP = QuickUnion_Find(uf, p);
  int rootQ = QuickUnion_Find(uf, q);

  if (rootP == rootQ) {
    return;
  }

  uf->entries[rootP] = rootQ;
  uf->countOfComponents--;
}

int QuickUnion_Find(UF uf, int p) {
  assert(uf);
  assert(0 <= p && p < uf->capacity);

  while (uf->entries[p] != p) {
    p = uf->entries[p];
  }
  return p;
}

inline bool QuickUnion_Connected(UF uf, int p, int q) {
  return QuickUnion_Find(uf, p) == QuickUnion_Find(uf, q);
}

bool QuickUnion_Count(UF uf) {
  assert(uf);
  return uf->countOfComponents;
}

