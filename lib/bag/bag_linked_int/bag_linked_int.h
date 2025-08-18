#include <stdbool.h>

#ifndef __linked_list_int_bag_h
#define __linked_list_int_bag_h

typedef int LLIntBagItem;
struct LLIntBagNode;

struct LLIntBag {
  struct LLIntBagNode *first;
  int size;
};
typedef struct LLIntBag *Bag;

struct LLIntBagIterator {
  struct LLIntBag *bag;
  struct LLIntBagNode *cur;
};
typedef struct LLIntBagIterator *BagIterator;

#define ITEM LLIntBagItem
#define ITER BagIterator

/**
 * Allocates and returns memory on heap required for `struct LLIntBag`. Doesn't
 * initialize the object, use `Bag_Init()` to initialize the `Bag` object.
 */
Bag Bag_Alloc();

/**
 * Frees the allocated `Bag` object on heap, uses `Bag_Clear()` to
 * deallocate/clear the memory for instance variables.
 */
void Bag_Free(Bag bag);

/** Initializes the instance variables of `Bag` object. */
void Bag_Init(Bag bag);

/** Clears and de-allocates any memory allocated for instance variables. */
void Bag_Clear(Bag bag);

void Bag_Add(Bag bag, ITEM item);
 int Bag_Size(Bag bag);
bool Bag_IsEmpty(Bag bag);

ITER BagIterator_Alloc();
void BagIterator_Free(ITER iterator);
void BagIterator_Init(ITER iterator, Bag bag);
void BagIterator_Clear(ITER iterator);
bool BagIterator_HasNext(ITER iterator);
 int BagIterator_GetNext(ITER iterator, ITEM *outItem);

#undef ITEM
#undef ITER

#endif // __linked_list_int_bag_h

