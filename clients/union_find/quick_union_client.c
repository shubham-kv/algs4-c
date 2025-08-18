#include <stdlib.h>
#include <stdio.h>
#include "quick_union.h"

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build
 *
 * ### Run
 * % ./build/bin/quick_union_client < tinyUF.txt
 *
 */
int main() {
  printf("** Quick Union **\n");
  printf("\n");

  int n = 0;
  fscanf(stdin, "%d", &n);

  int p, q;
  struct QuickUnion _uf, *uf = &_uf;
  QuickUnion_Init(uf, n);

  while (fscanf(stdin, "%d %d", &p, &q) != EOF) {
    bool connected = QuickUnion_Connected(uf, p, q);
    printf("connected(%d, %d): %s\n", p, q, connected ? "true" : "false");

    if (!connected) {
      QuickUnion_Union(uf, p, q);
      printf("union(%d, %d)\n", p, q);
    }
  }

  int count = QuickUnion_Count(uf);
  printf("count(): %d\n", count);
  printf("\n");

  QuickUnion_Clear(uf);

  return 0;
}

