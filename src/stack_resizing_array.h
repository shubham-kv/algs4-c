#include <stdlib.h>
#include <stdbool.h>

#ifndef __resizing_array_stack_h
#define __resizing_array_stack_h

struct ResizingArrayStack;
typedef struct ResizingArrayStack *Stack;
typedef const void *Item;

struct ResizingArrayStack {
  uint32_t capacity;
  uint32_t size;
  Item *items;
};

void Stack_Init(Stack stack);
void Stack_Clear(Stack stack);

void Stack_Push(Stack stack, Item item);
Item Stack_Pop(Stack stack);
 int Stack_Size(Stack stack);
bool Stack_IsEmpty(Stack stack);

#endif  // __resizing_array_stack_h

