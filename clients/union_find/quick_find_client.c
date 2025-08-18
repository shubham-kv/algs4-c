#include <stdlib.h>
#include <stdio.h>
#include "quick_find.h"

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build
 *
 * ### Run
 * % ./build/bin/stack_fixed_capacity_client < tinyUF.txt
 *
 */
int main() {
  printf("** Quick Find **\n");
  printf("\n");

  int n = 0;
  fscanf(stdin, "%d", &n);

  int p, q;
  struct QuickFind _uf, *uf = &_uf;
  QuickFind_Init(uf, n);

  while (fscanf(stdin, "%d %d", &p, &q) != EOF) {
    bool connected = QuickFind_Connected(uf, p, q);
    printf("connected(%d, %d): %s\n", p, q, connected ? "true" : "false");

    if (!connected) {
      QuickFind_Union(uf, p, q);
      printf("union(%d, %d)\n", p, q);
    }
  }

  int count = QuickFind_Count(uf);
  printf("count(): %d\n", count);
  printf("\n");

  QuickFind_Clear(uf);

  return 0;
}

