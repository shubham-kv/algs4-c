#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "quick_union_weighted.h"

int QuickUnion_Init(UF uf, uint32_t n) {
  UF_REQUIRE(uf != NULL, -1);

  uf->capacity = n;
  uf->entries = calloc(uf->capacity, sizeof(int));
  RETURN_ON_ERR_VAL(uf->entries != NULL ? 0 : -1);

  uf->sizes = calloc(uf->capacity, sizeof(int));
  RETURN_ON_ERR_VAL(uf->sizes != NULL ? 0 : -1);

  uf->countOfComponents = n;

  for (int i = 0; i < uf->capacity; i++) {
    uf->entries[i] = i;
    uf->sizes[i] = 1;
  }

  return 0;
}

int QuickUnion_Clear(UF uf) {
  UF_REQUIRE(uf != NULL, -1);

  free(uf->entries), (uf->entries = NULL);
  free(uf->sizes), (uf->sizes = NULL);
  memset(uf, 0, sizeof(struct WeightedQuickUnion));

  return 0;
}

int QuickUnion_Union(UF uf, int p, int q) {
  UF_REQUIRE(uf != NULL, -1);
  UF_REQUIRE(0 <= p && p < uf->capacity, -1);
  UF_REQUIRE(0 <= q && q < uf->capacity, -1);

  int rootP, rootQ;
  RETURN_ON_ERR_VAL(QuickUnion_Find(uf, p, &rootP));
  RETURN_ON_ERR_VAL(QuickUnion_Find(uf, q, &rootQ));

  if (rootP == rootQ) {
    return 0;
  }

  int sizeP = uf->sizes[rootP];
  int sizeQ = uf->sizes[rootQ];

  if (sizeP < sizeQ) {
    uf->entries[rootP] = rootQ;
    uf->sizes[rootQ] += sizeP;
  } else {
    uf->entries[rootQ] = rootP;
    uf->sizes[rootP] += sizeQ;
  }
  uf->countOfComponents--;

  return 0;
}

int QuickUnion_Find(UF uf, int p, int *outID) {
  UF_REQUIRE(uf != NULL, -1);
  UF_REQUIRE(outID != NULL, -1);
  UF_REQUIRE(0 <= p && p < uf->capacity, -1);

  while (uf->entries[p] != p) {
    uf->entries[p] = uf->entries[uf->entries[p]]; // path compression
    p = uf->entries[p];
  }
  *outID = p;

  return 0;
}

int QuickUnion_Connected(UF uf, int p, int q, bool *outIsConnected) {
  UF_REQUIRE(uf != NULL, -1);
  UF_REQUIRE(outIsConnected != NULL, -1);

  int rootP, rootQ;
  RETURN_ON_ERR_VAL(QuickUnion_Find(uf, p, &rootP));
  RETURN_ON_ERR_VAL(QuickUnion_Find(uf, q, &rootQ));
  *outIsConnected = (rootP == rootQ);

  return 0;
}

int QuickUnion_Count(UF uf, int *outCountOfComponents) {
  UF_REQUIRE(uf != NULL, -1);
  UF_REQUIRE(outCountOfComponents != NULL, -1);
  *outCountOfComponents = uf->countOfComponents;
  return 0;
}

