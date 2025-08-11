#include <stdlib.h>
#include <stdbool.h>

#ifndef __resizing_array_stack_h
#define __resizing_array_stack_h

typedef const void *Item;

struct ResizingArrayStack {
  uint32_t capacity;
  uint32_t size;
  Item *items;
};
typedef struct ResizingArrayStack *Stack;

void Stack_Init(Stack stack);
void Stack_Clear(Stack stack);

void Stack_Push(Stack stack, Item item);
Item Stack_Pop(Stack stack);
Item Stack_Peek(Stack stack);
 int Stack_Size(Stack stack);
bool Stack_IsEmpty(Stack stack);

struct RAStackIterator {
  struct ResizingArrayStack *stack;
  int i;
};
typedef struct RAStackIterator *StackIterator;

void StackIterator_Init(StackIterator iterator, Stack stack);
void StackIterator_Clear(StackIterator iterator);
bool StackIterator_HasNext(StackIterator iterator);
Item StackIterator_GetNext(StackIterator iterator);

#endif  // __resizing_array_stack_h

