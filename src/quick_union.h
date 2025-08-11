#include <stdint.h>
#include <stdbool.h>

#ifndef __quick_union_h
#define __quick_union_h

struct QuickUnion {
  int *entries;
  int capacity;
  int countOfComponents;
};
typedef struct QuickUnion *UF;

void QuickUnion_Init(UF uf, uint32_t n);
void QuickUnion_Clear(UF uf);
void QuickUnion_Union(UF uf, int p, int q);
 int QuickUnion_Find(UF uf, int p);
bool QuickUnion_Connected(UF uf, int p, int q);
bool QuickUnion_Count(UF uf);

#endif // __quick_union_h

