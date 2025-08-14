#include <stdlib.h>
#include <memory.h>
#include "stack_fixed_capacity.h"

void Stack_Init(Stack stack, uint32_t capacity) {
  stack->capacity = capacity;
  stack->size = 0;
  stack->items = calloc(capacity, sizeof(Item));
}

void Stack_Clear(Stack stack) {
  free(stack->items), (stack->items = NULL);
  memset(stack, 0, sizeof(struct FixedCapacityStack));
}

inline void Stack_Push(Stack stack, Item item) {
  if (stack->size < stack->capacity) {
   stack->items[stack->size++] = item;
  }
}

Item Stack_Pop(Stack stack) {
  if (Stack_IsEmpty(stack)) {
    return NULL;
  }

  Item top = stack->items[stack->size - 1];
  stack->items[--stack->size] = NULL;

  return top;
}

inline Item Stack_Peek(Stack stack) { 
  return Stack_IsEmpty(stack) ? NULL : stack->items[stack->size - 1];
}

inline int Stack_Size(Stack stack) {
  return stack->size;
}

inline bool Stack_IsEmpty(Stack stack) {
  return Stack_Size(stack) == 0;
}


inline void StackIterator_Init(StackIterator iterator, Stack stack) {
  iterator->stack = stack, iterator->i = stack->size - 1;
}

inline void StackIterator_Clear(StackIterator iterator) {
  memset(iterator, 0, sizeof(struct FCStackIterator));
}

inline bool StackIterator_HasNext(StackIterator iterator) {
  return 0 <= iterator->i && iterator->i < iterator->stack->size;
}

inline Item StackIterator_GetNext(StackIterator iterator) {
  return StackIterator_HasNext(iterator)
             ? iterator->stack->items[iterator->i--]
             : NULL;
}

