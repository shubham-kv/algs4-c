#include <stdbool.h>

#ifndef __queue_linked_list_h
#define __queue_linked_list_h

typedef const void *Item;

struct QueueNode;
struct LinkedListQueue;

struct LinkedListQueue {
  struct QueueNode *first;
  struct QueueNode *last;
  int size;
};
typedef struct LinkedListQueue *Queue;

void Queue_Init(Queue queue);
void Queue_Clear(Queue queue);

void Queue_Enqueue(Queue queue, Item item);
Item Queue_Dequeue(Queue queue);
Item Queue_Peek(Queue queue);
 int Queue_Size(Queue queue);
bool Queue_IsEmpty(Queue queue);

struct LLQueueIterator {
  struct LinkedListQueue *queue;
  struct QueueNode *cur;
};
typedef struct LLQueueIterator *QueueIterator;

void QueueIterator_Init(QueueIterator iterator, Queue queue);
void QueueIterator_Clear(QueueIterator iterator);
bool QueueIterator_HasNext(QueueIterator iterator);
Item QueueIterator_GetNext(QueueIterator iterator);

#endif // __queue_linked_list_h

