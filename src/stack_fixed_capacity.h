#include <stdlib.h>
#include <stdbool.h>

#ifndef __fixed_capacity_stack_h
#define __fixed_capacity_stack_h

struct FixedCapacityStack;
typedef struct FixedCapacityStack *Stack;
typedef const void *Item;

struct FixedCapacityStack {
  uint32_t capacity;
  uint32_t size;
  Item *items;
};

extern const size_t FIXED_CAPACITY_STACK_WIDTH;

void Stack_Init(Stack stack, uint32_t capacity);
void Stack_Clear(Stack stack);

void Stack_Push(Stack stack, Item item);
Item Stack_Pop(Stack stack);
 int Stack_Size(Stack stack);
bool Stack_IsEmpty(Stack stack);

#endif  // __fixed_capacity_stack_h

