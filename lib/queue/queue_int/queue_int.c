#include <errno.h>
#include <stdlib.h>
#include "queue_int.h"
#include "common_macros.h"

struct IntegerQueueNode;
typedef struct IntegerQueueNode *IntQueueNode;

#define QUEUE IntQueue
#define ITEM IntQueueItem
#define NODE IntQueueNode

struct IntegerQueueNode {
  NODE next;
  ITEM data;
};

struct IntegerQueue {
  NODE first;
  NODE last;
  size_t size;
};


QUEUE IntQueue_Create() {
  QUEUE queue = calloc(1, sizeof(struct IntegerQueue));
  if (IS_NULL(queue)) { errno = ENOMEM; return NULL; }

  queue->first = NULL;
  queue->last = NULL;
  queue->size = 0;
  return queue;
}

void IntQueue_Free(QUEUE *queue) {
  if (IS_NULL(queue) || IS_NULL(*queue)) { return; }

  while (!IntQueue_IsEmpty(*queue)) {
    IntQueue_Dequeue(*queue);
  }
  free(*queue), (*queue = NULL);
}

int IntQueue_Enqueue(QUEUE queue, ITEM data) {
  if (IS_NULL(queue)) { errno = EINVAL; return -1; }

  NODE node = calloc(1, sizeof(struct IntegerQueueNode));
  if (IS_NULL(node)) { errno = ENOMEM; return -1; }

  node->data = data;
  node->next = NULL;

  if (queue->last) {
    queue->last->next = node;
    queue->last = node;
  } else {
    queue->first = node;
    queue->last = queue->first;
  }
  queue->size++;
  return 0;
}

ITEM IntQueue_Dequeue(QUEUE queue) {
  if (IS_NULL(queue)) { errno = EINVAL; return -1; }
  if (IS_NULL(queue->first)) { errno = ENODATA; return -1; }

  NODE next = queue->first->next;
  ITEM data = queue->first->data;
  free(queue->first), (queue->first = NULL);

  if (next) {
    queue->first = next;
  } else {
    queue->first = NULL;
    queue->last = queue->first;
  }
  queue->size--;
  return data;
}

ITEM IntQueue_Peek(QUEUE queue) {
  if (IS_NULL(queue)) { errno = EINVAL; return -1; }
  if (IS_NULL(queue->first)) { errno = ENODATA; return -1; }

  return queue->first->data;
}

inline size_t IntQueue_Size(QUEUE queue) {
  return queue->size;
}

inline bool IntQueue_IsEmpty(QUEUE queue) {
  return IntQueue_Size(queue) == 0;
}


struct IntegerQueueIterator {
  QUEUE queue;
  NODE next;
};

#define ITER IntQueueIter

ITER IntQueueIter_Create(QUEUE queue) {
  if (IS_NULL(queue)) { errno = EINVAL; return NULL; }

  ITER iterator = calloc(1, sizeof(struct IntegerQueueIterator));
  if (IS_NULL(iterator)) { errno = ENOMEM; return NULL; }

  iterator->queue = queue;
  iterator->next = iterator->queue->first;

  return iterator;
}

void IntQueueIter_Free(ITER *iterator) {
  if (IS_NULL(iterator) || IS_NULL(*iterator)) { return; }

  free(*iterator), (*iterator = NULL);
}

inline bool IntQueueIter_HasNext(ITER iterator) {
  return !IS_NULL(iterator->next);
}

ITEM IntQueueIter_GetNext(ITER iterator) {
  if (IS_NULL(iterator)) { errno = EINVAL; return -1; }
  if (!IntQueueIter_HasNext(iterator)) { errno = ENODATA; return -1; }

  ITEM data = iterator->next->data;
  iterator->next = iterator->next->next;
  return data;
}

#undef ITER
#undef NODE
#undef ITEM
#undef QUEUE

