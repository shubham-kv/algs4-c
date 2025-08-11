#include <stdlib.h>
#include <memory.h>
#include "stack_fixed_capacity.h"

#define STACK_SIZE(stack) (((Stack) stack)->size)
#define IS_STACK_EMPTY(stack) (STACK_SIZE(stack) == 0)
#define IS_STACK_FULL(stack) (STACK_SIZE(stack) == ((Stack) stack)->capacity)

const size_t FIXED_CAPACITY_STACK_WIDTH = sizeof(struct FixedCapacityStack);
const size_t FC_STACK_ITERATOR_WIDTH = sizeof(struct FCStackIterator);

void Stack_Init(Stack stack, uint32_t capacity) {
  stack->capacity = capacity;
  stack->size = 0;
  stack->items = calloc(capacity, sizeof(Item));
}

void Stack_Clear(Stack stack) {
  free(stack->items), (stack->items = NULL);
  memset(stack, 0, FIXED_CAPACITY_STACK_WIDTH);
}

inline void Stack_Push(Stack stack, Item item) {
  !IS_STACK_FULL(stack) && (stack->items[stack->size++] = item);
}

Item Stack_Pop(Stack stack) {
  if (IS_STACK_EMPTY(stack)) {
    return NULL;
  }

  Item top = stack->items[stack->size - 1];
  stack->items[--stack->size] = NULL;

  return top;
}

inline Item Stack_Peek(Stack stack) { 
  return IS_STACK_EMPTY(stack) ? NULL : stack->items[stack->size - 1];
}

inline int Stack_Size(Stack stack) {
  return STACK_SIZE(stack);
}

inline bool Stack_IsEmpty(Stack stack) {
  return IS_STACK_EMPTY(stack);
}


inline void StackIterator_Init(StackIterator iterator, Stack stack) {
  iterator->stack = stack, iterator->i = stack->size - 1;
}

inline void StackIterator_Clear(StackIterator iterator) {
  memset(iterator, 0, FC_STACK_ITERATOR_WIDTH);
}

inline bool StackIterator_HasNext(StackIterator iterator) {
  return 0 <= iterator->i && iterator->i < iterator->stack->size;
}

inline Item StackIterator_GetNext(StackIterator iterator) {
  return StackIterator_HasNext(iterator)
             ? iterator->stack->items[iterator->i--]
             : NULL;
}

#undef STACK_SIZE
#undef IS_STACK_EMPTY
#undef IS_STACK_FULL

