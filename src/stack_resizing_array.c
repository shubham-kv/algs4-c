#include <stdlib.h>
#include <memory.h>
#include "stack_resizing_array.h"

#define INITIAL_CAPACITY 8
#define STACK_SIZE(stack) (((Stack) stack)->size)
#define IS_STACK_EMPTY(stack) (STACK_SIZE(stack) == 0)
#define IS_STACK_FULL(stack) (STACK_SIZE(stack) == ((Stack) stack)->capacity)

static void resize(Stack stack, uint32_t newCapacity);

const size_t RESIZING_ARRAY_STACK_WIDTH = sizeof(struct ResizingArrayStack);

void Stack_Init(Stack stack) {
  stack->capacity = INITIAL_CAPACITY;
  stack->size = 0;
  stack->items = calloc(stack->capacity, sizeof(Item));
}

void Stack_Clear(Stack stack) {
  free(stack->items);
  memset(stack, 0, RESIZING_ARRAY_STACK_WIDTH);
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

#undef INITIAL_CAPACITY
#undef STACK_SIZE
#undef IS_STACK_EMPTY
#undef IS_STACK_FULL

