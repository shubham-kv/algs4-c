#include <stdlib.h>
#include <memory.h>
#include "stack_fixed_capacity.h"

#define STACK_SIZE(stack) (((Stack) stack)->size)
#define IS_STACK_EMPTY(stack) (((Stack) stack)->size == 0)
#define IS_STACK_FULL(stack) (((Stack) stack)->size == ((Stack) stack)->capacity)

const size_t FIXED_CAPACITY_STACK_WIDTH = sizeof(struct FixedCapacityStack *);

void Stack_Init(Stack stack, uint32_t capacity) {
  stack->capacity = capacity;
  stack->size = 0;
  stack->items = calloc(capacity, sizeof(Item));
}

void Stack_Clear(Stack stack) {
  free(stack->items);
  memset(stack, 0, FIXED_CAPACITY_STACK_WIDTH);
}

inline void Stack_Push(Stack stack, Item item) {
  !IS_STACK_FULL(stack) && (stack->items[stack->size++] = item);
}

inline Item Stack_Pop(Stack stack) {
  return IS_STACK_EMPTY(stack) ? NULL : stack->items[--stack->size];
}

inline int Stack_Size(Stack stack) {
  return STACK_SIZE(stack);
}

inline bool Stack_IsEmpty(Stack stack) {
  return IS_STACK_EMPTY(stack);
}

#undef STACK_SIZE
#undef IS_STACK_EMPTY
#undef IS_STACK_FULL

