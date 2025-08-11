#include <stdlib.h>
#include <stdbool.h>

#ifndef __fixed_capacity_stack_h
#define __fixed_capacity_stack_h

typedef const void *Item;

struct FixedCapacityStack {
  uint32_t capacity;
  uint32_t size;
  Item *items;
};
typedef struct FixedCapacityStack *Stack;

void Stack_Init(Stack stack, uint32_t capacity);
void Stack_Clear(Stack stack);

void Stack_Push(Stack stack, Item item);
Item Stack_Pop(Stack stack);
Item Stack_Peek(Stack stack);
 int Stack_Size(Stack stack);
bool Stack_IsEmpty(Stack stack);

struct FCStackIterator {
  Stack stack;
  int i;
};
typedef struct FCStackIterator *StackIterator;

void StackIterator_Init(StackIterator iterator, Stack stack);
void StackIterator_Clear(StackIterator iterator);
bool StackIterator_HasNext(StackIterator iterator);
Item StackIterator_GetNext(StackIterator iterator);

#endif  // __fixed_capacity_stack_h

