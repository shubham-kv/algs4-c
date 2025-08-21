#include <errno.h>
#include <stdlib.h>
#include "stack_int.h"
#include "common_macros.h"

struct IntegerStackNode;
typedef struct IntegerStackNode *IntStackNode;

#define STACK IntStack
#define ITEM IntStackItem
#define NODE IntStackNode

struct IntegerStackNode {
  NODE next;
  ITEM data;
};

struct IntegerStack {
  NODE top;
  size_t size;
};


STACK IntStack_Create() {
  STACK stack = calloc(1, sizeof(struct IntegerStack));
  if (IS_NULL(stack)) { errno = ENOMEM; return NULL; }

  stack->top = NULL, stack->size = 0;
  return stack;
}

void IntStack_Free(STACK *stack) {
  if (IS_NULL(stack) || IS_NULL(*stack)) { return; }

  while (!IntStack_IsEmpty(*stack)) {
    IntStack_Pop(*stack);
  }

  free(*stack), (*stack = NULL);
}

int IntStack_Push(STACK stack, ITEM data) {
  if (IS_NULL(stack)) { errno = EINVAL; return -1; }

  NODE node = calloc(1, sizeof(struct IntegerStackNode));
  if (IS_NULL(node)) { errno = ENOMEM; return -1; }

  node->data = data;
  node->next = stack->top;
  stack->top = node;
  stack->size++;
  return 0;
}

ITEM IntStack_Pop(STACK stack) {
  if (IS_NULL(stack)) { errno = EINVAL; return -1; }
  if (IntStack_IsEmpty(stack)) { errno = ENODATA; return -1; }

  NODE next = stack->top->next;
  ITEM data = stack->top->data;
  free(stack->top), (stack->top = NULL);

  stack->top = next;
  stack->size--;
  return data;
}

ITEM IntStack_Peek(STACK stack) {
  if (IS_NULL(stack)) { errno = EINVAL; return -1; }
  if (IntStack_IsEmpty(stack)) { errno = ENODATA; return -1; }

  return stack->top->data;
}

inline size_t IntStack_Size(STACK stack) {
  return stack->size;
}

inline bool IntStack_IsEmpty(STACK stack) {
  return IntStack_Size(stack) == 0;
}


struct IntegerStackIterator {
  STACK stack;
  NODE next;
};

#define ITER IntStackIter

ITER IntStackIter_Create(STACK stack) {
  if (IS_NULL(stack)) { errno = EINVAL; return NULL; }

  ITER iterator = calloc(1, sizeof(struct IntegerStackIterator));
  if (IS_NULL(iterator)) { errno = ENOMEM; return NULL; }

  iterator->stack = stack;
  iterator->next = stack->top;
  return iterator;
}

void IntStackIter_Free(ITER *iterator) {
  if (IS_NULL(iterator) || IS_NULL(*iterator)) { return; }
  free(*iterator), (*iterator = NULL);
}

inline bool IntStackIter_HasNext(ITER iterator) {
  return IS_NULL(iterator->next) ? false : true;
}

int IntStackIter_GetNext(ITER iterator, ITEM *out) {
  if (IS_NULL(iterator)) { errno = EINVAL; return -1; }
  if (!IntStackIter_HasNext(iterator)) { errno = ENODATA; return -1; }

  *out = iterator->next->data;
  iterator->next = iterator->next->next;
  return 0;
}

#undef ITER
#undef NODE
#undef ITEM
#undef STACK

