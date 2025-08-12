#include <stdlib.h>
#include <stdio.h>
#include "quick_union_weighted.h"

/**
 * ### Compile
 * `% mkdir build`
 * `% gcc src/quick_union_weighted_client.c src/quick_union_weighted.c -o build/quick_union_weighted_client.out`
 *
 * ### Run
 * `% build/quick_union_weighted_client.out < tinyUF.txt`
 *
 */
int main() {
  int n = 0, p, q;
  fscanf(stdin, "%d", &n);

  struct WeightedQuickUnion _uf, *uf = &_uf;
  RETURN_ON_ERR_VAL(QuickUnion_Init(uf, n));

  while (fscanf(stdin, "%d %d", &p, &q) != EOF) {
    bool connected = false;
    RETURN_ON_ERR_VAL(QuickUnion_Connected(uf, p, q, &connected));

    printf("connected(%d, %d): %s\n", p, q, connected ? "true" : "false");

    if (!connected) {
      RETURN_ON_ERR_VAL(QuickUnion_Union(uf, p, q));

      printf("union(%d, %d)\n", p, q);
    }
  }

  int count;
  RETURN_ON_ERR_VAL(QuickUnion_Count(uf, &count));

  printf("count(): %d\n", count);
  RETURN_ON_ERR_VAL(QuickUnion_Clear(uf)); (uf = NULL);

  return 0;
}

