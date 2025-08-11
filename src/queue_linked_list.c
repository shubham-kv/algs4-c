#include <memory.h>
#include <stdlib.h>
#include "queue_linked_list.h"

struct QueueNode {
  struct QueueNode *next;
  Item data;
};
typedef struct QueueNode *Node;

#define SIZEOF_QUEUE (sizeof(struct LinkedListQueue))
#define SIZEOF_QUEUE_NODE (sizeof(struct QueueNode))
#define SIZEOF_QUEUE_ITERATOR (sizeof(struct LLQueueIterator))

inline void Queue_Init(Queue queue) {
  (queue->first = (queue->last = NULL)), (queue->size = 0);
}

void Queue_Clear(Queue queue) {
  while (!Queue_IsEmpty(queue)) {
    Queue_Dequeue(queue);
  }
  memset(queue, 0, SIZEOF_QUEUE);
}

void Queue_Enqueue(Queue queue, Item item) {
  Node node = calloc(1, SIZEOF_QUEUE_NODE);
  node->data = item;

  if (queue->last) {
    queue->last->next = node;
    queue->last = node;
  } else {
    queue->first = node;
    queue->last = queue->first;
  }
  queue->size++;
}

Item Queue_Dequeue(Queue queue) {
  if (Queue_IsEmpty(queue)) {
    return NULL;
  }

  Item firstItem = queue->first->data;
  Node next = queue->first->next;
  free(queue->first), (queue->first = NULL);

  if (next) {
    queue->first = next;
  } else {
    queue->first = NULL;
    queue->last = queue->first;
  }
  queue->size--;

  return firstItem;
}

inline Item Queue_Peek(Queue queue) {
  return Queue_IsEmpty(queue) ? NULL : queue->first->data;
}

inline int Queue_Size(Queue queue) {
  return queue->size;
}

inline bool Queue_IsEmpty(Queue queue) {
  return Queue_Size(queue) == 0;
}


inline void QueueIterator_Init(QueueIterator iterator, Queue queue) {
  (iterator->queue = queue), (iterator->cur = iterator->queue->first);
}

inline void QueueIterator_Clear(QueueIterator iterator) {
  memset(iterator, 0, SIZEOF_QUEUE_ITERATOR);
}

inline bool QueueIterator_HasNext(QueueIterator iterator) {
  return iterator->cur != NULL;
}

Item QueueIterator_GetNext(QueueIterator iterator) {
  if (!QueueIterator_HasNext(iterator)) {
    return NULL;
  }

  Item firstItem = iterator->cur->data;
  iterator->cur = iterator->cur->next;

  return firstItem;
}

#undef SIZEOF_QUEUE
#undef SIZEOF_QUEUE_NODE
#undef SIZEOF_QUEUE_ITERATOR

