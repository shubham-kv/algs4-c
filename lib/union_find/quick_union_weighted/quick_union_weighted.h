#include <stdlib.h>
#include <stdbool.h>

#ifndef __weighted_quick_union_h
#define __weighted_quick_union_h

struct WeightedQuickUnion {
  int *entries;
  int *sizes;
  int capacity;
  int countOfComponents;
};

typedef struct WeightedQuickUnion *UF;

int QuickUnion_Init(UF uf, uint32_t n);
int QuickUnion_Clear(UF uf);
int QuickUnion_Union(UF uf, int p, int q);
int QuickUnion_Find(UF uf, int p, int *outId);
int QuickUnion_Connected(UF uf, int p, int q, bool *outIsConnected);
int QuickUnion_Count(UF uf, int *outCountOfComponents);

#ifndef NDEBUG
#define UF_REQUIRE(cond, retVal)                                               \
  (assert((cond) && "Expected non-null uf ptr, received NULL"))
#else
#define UF_REQUIRE(cond, retVal)                                      \
  do {                                                                         \
    bool _ok = (cond);                                                         \
    if (!_ok) {                                                                \
      fprintf(stderr, "UF_REQUIRE failed: %s (at %s:%d)\n", #cond, __FILE__,   \
              __LINE__);                                                       \
      return retVal;                                                           \
    }                                                                          \
  } while (0)
#endif // NDEBUG

#define RETURN_ON_ERR_VAL(exp)                                                 \
   do {                                                                        \
     int retVal = (exp);                                                       \
     if (retVal != 0) {                                                        \
       return retVal;                                                          \
     }                                                                         \
   } while (0)

#endif // __weighted_quick_union_h

