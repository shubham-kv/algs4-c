#include <criterion/criterion.h>
#include "queue_int.h"

static IntQueue queue;
static const int SUCCESS_RETURN_CODE = 0;
static const int ERR_RETURN_CODE = -1;

static void setup() {
  queue = IntQueue_Create();
  cr_assert(queue != NULL);
}

static void teardown() {
  IntQueue_Free(&queue);
}


Test(
    int_queue_enqueue,
    enqueues_items,
    .init = setup,
    .fini = teardown
) {
  cr_assert(IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), 0);
  cr_assert_eq(IntQueue_Peek(queue), ERR_RETURN_CODE);

  IntQueue_Enqueue(queue,  -1);
  IntQueue_Enqueue(queue,   0);
  IntQueue_Enqueue(queue,  +1);

  cr_assert(!IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), 3);
  cr_assert_eq(IntQueue_Peek(queue), -1);

  IntQueueIter iterator = IntQueueIter_Create(queue);
  cr_assert(iterator);

  int expected, actual;

  expected = -1;
  cr_assert(IntQueueIter_HasNext(iterator));
  actual = IntQueueIter_GetNext(iterator);
  cr_assert_eq(actual, expected, "Expected next integer to be %d, got %d",
               expected, actual);

  expected = 0;
  cr_assert(IntQueueIter_HasNext(iterator));
  actual = IntQueueIter_GetNext(iterator);
  cr_assert_eq(actual, expected, "Expected next integer to be %d, got %d",
               expected, actual);

  expected = 1;
  cr_assert(IntQueueIter_HasNext(iterator));
  actual = IntQueueIter_GetNext(iterator);
  cr_assert_eq(actual, expected, "Expected next integer to be %d, got %d",
               expected, actual);

  cr_assert(!IntQueueIter_HasNext(iterator));
  cr_assert_eq(IntQueueIter_GetNext(iterator), ERR_RETURN_CODE);

  IntQueueIter_Free(&iterator);
}


Test(
    int_queue_enqueue,
    enqueues_large_number_of_items,
    .init = setup,
    .fini = teardown
) {
  cr_assert(IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), 0);
  cr_assert_eq(IntQueue_Peek(queue), ERR_RETURN_CODE);

  const int integersSize = INT16_MAX * 2;
  int integers[integersSize];

  for (int i = 0, val = INT16_MIN; i < integersSize; i++, val++) {
    integers[i] = val;
    IntQueue_Enqueue(queue, val);
  }

  cr_assert(!IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), integersSize);
  cr_assert_eq(IntQueue_Peek(queue), integers[0]);

  IntQueueIter iterator = IntQueueIter_Create(queue);
  cr_assert(iterator);
  int expected, actual;

  for (int i = 0; i < integersSize; i++) {
    expected = integers[i];
    cr_assert(IntQueueIter_HasNext(iterator));

    actual = IntQueueIter_GetNext(iterator);
    cr_assert_eq(actual, expected, "Expected next integer to be %d, got %d",
                 expected, actual);
  }

  cr_assert(!IntQueueIter_HasNext(iterator));
  cr_assert_eq(IntQueueIter_GetNext(iterator), ERR_RETURN_CODE);

  IntQueueIter_Free(&iterator);
}


Test(
    int_queue_dequeue,
    dequeues_items,
    .init = setup,
    .fini = teardown
) {
  cr_assert(IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), 0);
  cr_assert_eq(IntQueue_Dequeue(queue), ERR_RETURN_CODE);

  IntQueue_Enqueue(queue,  -1);
  IntQueue_Enqueue(queue,   0);
  IntQueue_Enqueue(queue,  +1);

  cr_assert(!IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), 3);

  int dequeuedInt, expectedInt;

  expectedInt = -1;
  cr_assert(!IntQueue_IsEmpty(queue));
  dequeuedInt = IntQueue_Dequeue(queue);
  cr_assert_eq(dequeuedInt, expectedInt, "Expected %d to be dequeued, got %d",
               expectedInt, dequeuedInt);

  expectedInt = 0;
  cr_assert(!IntQueue_IsEmpty(queue));
  dequeuedInt = IntQueue_Dequeue(queue);
  cr_assert_eq(dequeuedInt, expectedInt, "Expected %d to be dequeued, got %d",
               expectedInt, dequeuedInt);

  expectedInt = 1;
  cr_assert(!IntQueue_IsEmpty(queue));
  dequeuedInt = IntQueue_Dequeue(queue);
  cr_assert_eq(dequeuedInt, expectedInt, "Expected %d to be dequeued, got %d",
               expectedInt, dequeuedInt);
}


Test(
    int_queue_dequeue,
    dequeues_large_number_of_items,
    .init = setup,
    .fini = teardown
) {
  cr_assert(IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), 0);
  cr_assert_eq(IntQueue_Dequeue(queue), ERR_RETURN_CODE);

  const int integersSize = INT16_MAX;
  int integers[integersSize];

  for (int i = 0, val = INT16_MIN; i < integersSize; i++, val++) {
    integers[i] = val;
    IntQueue_Enqueue(queue, val);
  }

  cr_assert(!IntQueue_IsEmpty(queue));
  cr_assert_eq(IntQueue_Size(queue), integersSize);

  int expected, actual;

  for (int i = 0; i < integersSize; i++) {
    expected = integers[i];
    cr_assert(!IntQueue_IsEmpty(queue));

    actual = IntQueue_Dequeue(queue);
    cr_assert_eq(actual, expected, "Expected %d to be dequeued, got %d",
                 expected, actual);
  }
}

