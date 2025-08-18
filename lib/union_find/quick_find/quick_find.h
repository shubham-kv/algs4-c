#include <stdlib.h>
#include <stdbool.h>

#ifndef __quick_find_h 
#define __quick_find_h 

struct QuickFind {
  int *entries;
  uint32_t capacity;
  int components;
};
typedef struct QuickFind *UF;

void QuickFind_Init(UF uf, uint32_t n);
void QuickFind_Clear(UF uf);

/** Add connection between p and q */
void QuickFind_Union(UF uf, int p, int q);

/** Get the component identifier for p */
int QuickFind_Find(UF uf, int p);

/** Are p and q connected? */
bool QuickFind_Connected(UF uf, int p, int q);

/** Number of connected components */
int QuickFind_Count(UF uf);

#endif // __quick_find_h 

