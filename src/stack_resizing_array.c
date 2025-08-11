#include <stdlib.h>
#include <memory.h>
#include "stack_resizing_array.h"

#define INITIAL_CAPACITY 8
#define STACK_SIZE(stack) (((Stack) stack)->size)
#define IS_STACK_EMPTY(stack) (STACK_SIZE(stack) == 0)
#define IS_STACK_FULL(stack) (STACK_SIZE(stack) == ((Stack) stack)->capacity)

void Stack_Init(Stack stack) {
  stack->capacity = INITIAL_CAPACITY;
  stack->size = 0;
  stack->items = calloc(stack->capacity, sizeof(Item));
}

void Stack_Clear(Stack stack) {
  free(stack->items), (stack->items = NULL);
  memset(stack, 0, sizeof(struct ResizingArrayStack));
}

static void resize(Stack stack, uint32_t newCapacity) {
  stack->capacity = newCapacity;
  stack->items = realloc(stack->items, newCapacity * sizeof(Item));
}

void Stack_Push(Stack stack, Item item) {
  if (IS_STACK_FULL(stack)) {
    resize(stack, stack->capacity * 2);
  }
  stack->items[stack->size++] = item;
}

Item Stack_Peek(Stack stack) {
  return IS_STACK_EMPTY(stack) ? NULL : stack->items[stack->size - 1];
}

Item Stack_Pop(Stack stack) {
  if (IS_STACK_EMPTY(stack)) {
    return NULL;
  }

  Item top = stack->items[stack->size - 1];
  stack->items[--stack->size] = NULL;

  if (stack->size < stack->capacity / 4) {
    resize(stack, stack->capacity / 2);
  }

  return top;
}

inline int Stack_Size(Stack stack) {
  return STACK_SIZE(stack);
}

inline bool Stack_IsEmpty(Stack stack) {
  return IS_STACK_EMPTY(stack);
}


inline void StackIterator_Init(StackIterator iterator, Stack stack) {
  iterator->stack = stack, iterator->i = iterator->stack->size - 1;
}

inline void StackIterator_Clear(StackIterator iterator) {
  memset(iterator, 0, sizeof(struct RAStackIterator));
}

inline bool StackIterator_HasNext(StackIterator iterator) {
  return 0 <= iterator->i && iterator->i < iterator->stack->size;
}

inline Item StackIterator_GetNext(StackIterator iterator) {
  return StackIterator_HasNext(iterator)
      ? iterator->stack->items[iterator->i--]
      : NULL;
}

#undef INITIAL_CAPACITY
#undef STACK_SIZE
#undef IS_STACK_EMPTY
#undef IS_STACK_FULL

