#include <memory.h>
#include <stdlib.h>
#include "bag_linked.h"

struct BagNode {
  struct BagNode *next;
  BagItem item;
};
typedef struct BagNode *Node;

inline void Bag_Init(Bag bag) {
  (bag->first = NULL), (bag->size = 0);
}

static void removeFirstNode(Bag bag) {
  if (Bag_IsEmpty(bag)) {
    return;
  }

  Node next = bag->first->next;
  free(bag->first), (bag->first = NULL);
  bag->first = next;
  bag->size--;
}

void Bag_Clear(Bag bag) {
  while (!Bag_IsEmpty(bag)) {
    removeFirstNode(bag);
  }
  memset(bag, 0, sizeof(struct LinkedListBag));
}

void Bag_Add(Bag bag, BagItem item) {
  Node node = calloc(1, sizeof(struct BagNode));
  node->item = item;
  node->next = bag->first;
  bag->first = node;
  bag->size++;
}

inline int Bag_Size(Bag bag) {
  return bag->size;
}

inline bool Bag_IsEmpty(Bag bag) {
  return Bag_Size(bag) == 0;
}


inline void BagIterator_Init(BagIterator iterator, Bag bag) {
  (iterator->bag = bag), (iterator->cur = iterator->bag->first);
}

inline void BagIterator_Clear(BagIterator iterator) {
  memset(iterator, 0, sizeof(struct LLBagIterator));
}

inline bool BagIterator_HasNext(BagIterator iterator) {
  return iterator->cur != NULL;
}

BagItem BagIterator_GetNext(BagIterator iterator) {
  if (!BagIterator_HasNext(iterator)) {
    return NULL;
  }

  BagItem item = iterator->cur->item;
  iterator->cur = iterator->cur->next;
  return item;
}

