#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include "quick_find.h"

void QuickFind_Init(UF uf, uint32_t n) {
  assert(uf);
  uf->capacity = n;
  uf->entries = calloc(n, sizeof(int));
  uf->components = n;

  for (int i = 0; i < uf->capacity; i++) {
    uf->entries[i] = i;
  }
}

void QuickFind_Clear(UF uf) {
  assert(uf);
  free(uf->entries), (uf->entries = NULL);
  memset(uf, 0, sizeof(struct QuickFind));
}

void QuickFind_Union(UF uf, int p, int q) {
  assert(uf);
  assert(0 <= p && p < uf->capacity);
  assert(0 <= q && q < uf->capacity);

  int entryAtP = uf->entries[p];
  int entryAtQ = uf->entries[q];

  if (entryAtP == entryAtQ) {
    return;
  }

  for (int i = 0; i < uf->capacity; i++) {
    if (uf->entries[i] == entryAtP) {
      uf->entries[i] = entryAtQ;
    }
  }
  uf->components--;
}

int QuickFind_Find(UF uf, int p) {
  assert(uf), assert(0 <= p && p < uf->capacity);
  return uf->entries[p];
}

inline bool QuickFind_Connected(UF uf, int p, int q) {
  return QuickFind_Find(uf, p) == QuickFind_Find(uf, q);
}

int QuickFind_Count(UF uf) {
  assert(uf);
  return uf->components;
}

