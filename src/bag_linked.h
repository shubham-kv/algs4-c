#include <stdbool.h>

#ifndef __bag_linked_h
#define __bag_linked_h

typedef const void *BagItem;

struct BagNode;
struct LinkedListBag;

struct LinkedListBag {
  struct BagNode *first;
  int size;
};
typedef struct LinkedListBag *Bag;

void Bag_Init(Bag bag);
void Bag_Clear(Bag bag);
void Bag_Add(Bag bag, BagItem item);
 int Bag_Size(Bag bag);
bool Bag_IsEmpty(Bag bag);

struct LLBagIterator {
  struct LinkedListBag *bag;
  struct BagNode *cur;
};
typedef struct LLBagIterator *BagIterator;

void BagIterator_Init(BagIterator iterator, Bag bag);
void BagIterator_Clear(BagIterator iterator);
bool BagIterator_HasNext(BagIterator iterator);
BagItem BagIterator_GetNext(BagIterator iterator);

#endif // __bag_linked_h

