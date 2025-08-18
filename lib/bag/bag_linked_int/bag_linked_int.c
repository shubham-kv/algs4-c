#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include "bag_linked_int.h"

#define ITEM LLIntBagItem
#define ITER BagIterator

struct LLIntBagNode {
  struct LLIntBagNode *next;
  ITEM data;
};
typedef struct LLIntBagNode *Node;

inline Bag Bag_Alloc() {
  return calloc(1, sizeof(struct LLIntBag));
}
inline void Bag_Free(Bag bag) {
  Bag_Clear(bag), free(bag), (bag = NULL);
}

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
  memset(bag, 0, sizeof(struct LLIntBag));
}

void Bag_Add(Bag bag, ITEM data) {
  Node node = calloc(1, sizeof(struct LLIntBagNode));
  node->next = bag->first;
  node->data = data;
  bag->first = node;
  bag->size++;
}

inline int Bag_Size(Bag bag) {
  return bag->size;
}

inline bool Bag_IsEmpty(Bag bag) {
  return Bag_Size(bag) == 0;
}


inline ITER BagIterator_Alloc() {
  return calloc(1, sizeof(struct LLIntBagIterator));
}
inline void BagIterator_Free(ITER iterator) {
  BagIterator_Clear(iterator), free(iterator), (iterator = NULL);
}
inline void BagIterator_Init(ITER iterator, Bag bag) {
  (iterator->bag = bag), (iterator->cur = iterator->bag->first);
}
inline void BagIterator_Clear(ITER iterator) {
  memset(iterator, 0, sizeof(struct LLIntBagIterator));
}
inline bool BagIterator_HasNext(ITER iterator) {
  return iterator->cur != NULL;
}

int BagIterator_GetNext(ITER iterator, ITEM *outItem) {
  if (!BagIterator_HasNext(iterator) || outItem == NULL) {
    return -1;
  }

  *outItem = iterator->cur->data;
  iterator->cur = iterator->cur->next;
  return 0;
}

#undef ITEM
#undef ITER

