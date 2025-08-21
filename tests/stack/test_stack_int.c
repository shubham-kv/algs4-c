#include <criterion/criterion.h>
#include <errno.h>
#include <stdint.h>
#include "stack_int.h"

static IntStack stack;
static const int ERR_RETURN_CODE = -1;
static const int SUCCESS_RETURN_CODE = 0;

static void setup() {
  stack = IntStack_Create();
  cr_assert(stack != NULL);
}

static void teardown() {
  IntStack_Free(&stack);
}

Test(
    int_stack_push,
    pushes_data_onto_stack,
    .init = setup,
    .fini = teardown
) {
  IntStack_Push(stack, -1);
  IntStack_Push(stack,  0);
  IntStack_Push(stack, 10);

  cr_assert(IntStack_Size(stack) == 3);
  cr_assert(IntStack_IsEmpty(stack) == false);

  IntStackIter iterator = IntStackIter_Create(stack);
  cr_assert(iterator != NULL);

  int64_t integer;
  cr_assert(IntStackIter_HasNext(iterator) == true);
  cr_assert(IntStackIter_GetNext(iterator, &integer) == SUCCESS_RETURN_CODE);
  cr_assert(10 == integer);

  cr_assert(IntStackIter_HasNext(iterator) == true);
  cr_assert(IntStackIter_GetNext(iterator, &integer) == SUCCESS_RETURN_CODE);
  cr_assert(0 == integer);

  cr_assert(IntStackIter_HasNext(iterator) == true);
  cr_assert(IntStackIter_GetNext(iterator, &integer) == SUCCESS_RETURN_CODE);
  cr_assert(-1 == integer);

  cr_assert(IntStackIter_HasNext(iterator) == false);
  cr_assert(IntStackIter_GetNext(iterator, &integer) == ERR_RETURN_CODE);

  IntStackIter_Free(&iterator);
}


Test(
    int_stack_pop,
    pops_data_from_stack,
    .init = setup,
    .fini = teardown
) {
  IntStack_Push(stack, -1);
  IntStack_Push(stack,  0);
  IntStack_Push(stack, 10);

  cr_assert(IntStack_IsEmpty(stack) == false);
  cr_assert(IntStack_Pop(stack) == 10);

  cr_assert(IntStack_IsEmpty(stack) == false);
  cr_assert(IntStack_Pop(stack) ==  0);

  cr_assert(IntStack_IsEmpty(stack) == false);
  cr_assert(IntStack_Pop(stack) == -1);

  cr_assert(IntStack_IsEmpty(stack) == true);
  cr_assert(IntStack_Pop(stack) == ERR_RETURN_CODE);
}


Test(
    int_stack_push,
    exhaustive_pushes_onto_stack,
    .init = setup,
    .fini = teardown
) {
  const int integersSize = INT16_MAX;
  int64_t integers[integersSize];

  for (int i = 0; i < integersSize; i++) {
    integers[i] = i;
    cr_assert(IntStack_Push(stack, i) == SUCCESS_RETURN_CODE);
  }

  cr_assert(IntStack_Size(stack) == integersSize);

  int i = 0;
  IntStackIter iterator = IntStackIter_Create(stack);
  cr_assert(iterator != NULL);

  cr_assert(IntStackIter_HasNext(iterator) == true);

  for (i = 0; IntStackIter_HasNext(iterator); i++) {
    int64_t integer = 0;
    cr_assert(IntStackIter_GetNext(iterator, &integer) == SUCCESS_RETURN_CODE);

    const int expectedInteger = integers[(integersSize - 1) - i];
    cr_assert(integer == expectedInteger,
              "Expected next integer to be %d, it is %lld", expectedInteger,
              integer);
  }

  cr_assert(i == integersSize, "Expected the iterator to consume all %d items, "
                               "but %d were consumed", integersSize, i);

  IntStackIter_Free(&iterator);
}


Test(
    int_stack_pop,
    exhaustive_pops_from_stack,
    .init = setup,
    .fini = teardown
) {
  const int integersSize = INT16_MAX;
  int64_t integers[integersSize];

  for (int i = 0; i < integersSize; i++) {
    integers[i] = i;
    cr_assert(IntStack_Push(stack, i) == SUCCESS_RETURN_CODE);
  }

  cr_assert(IntStack_Size(stack) == integersSize);

  int i = 0;
  for (i = 0; !IntStack_IsEmpty(stack); i++) {
    const int expectedInteger = integers[(integersSize - 1) - i];
    cr_assert(IntStack_Pop(stack) == expectedInteger);
  }

  cr_assert(i == integersSize, "Expected the stack to pop all %d items, "
                               "but only %d were popped", integersSize, i);
}

