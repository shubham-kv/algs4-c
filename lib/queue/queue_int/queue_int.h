#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef __queue_int_h
#define __queue_int_h

/** Queue of integers (FIFO order) */
struct IntegerQueue;
typedef struct IntegerQueue *IntQueue;
typedef int64_t IntQueueItem;

#define QUEUE IntQueue
#define ITEM IntQueueItem

/** Creates a growable queue of integers on heap. */
QUEUE IntQueue_Create();
void IntQueue_Free(QUEUE *queue);

/** Adds an item to the queue, returns `0` on success or `-1` otherwise. */
int IntQueue_Enqueue(QUEUE queue, ITEM item);

/** Removes the least recently added item from the queue, returns the item on
 * success or `-1` otherwise, use `IntQueue_Size` or `IntQueue_IsEmpty` to
 * determine if queue contains integers. */
ITEM IntQueue_Dequeue(QUEUE queue);

/** Returns the least recently added item to the queue, returns `-1` on error. */
ITEM IntQueue_Peek(QUEUE queue);

/** Returns the number of items in the queue, crashes if `queue` is `NULL`. */
size_t IntQueue_Size(QUEUE queue);

/** Returns a boolean indicating whether the queue is empty, crashes if `queue`
 * is `NULL`. */
bool IntQueue_IsEmpty(QUEUE queue);


/** Iterator to yield integers in the queue (FIFO order). */
struct IntegerQueueIterator;
typedef struct IntegerQueueIterator *IntQueueIter;

#define ITER IntQueueIter

/** Creates an iterator on the heap to yield integers in the queue (FIFO order).
 */
ITER IntQueueIter_Create(QUEUE queue);
void IntQueueIter_Free(ITER *iterator);

/** Returns a boolean indicating whether there is a next item to consume.
 * Crashes if `iterator` is `NULL`. */
bool IntQueueIter_HasNext(ITER iterator);

/** Consumes and returns the next item in the queue if there is one otherwise
 * sets `errno` and returns `-1`. */
ITEM IntQueueIter_GetNext(ITER iterator);

#undef ITER
#undef ITEM
#undef QUEUE

#endif // __queue_int_h

