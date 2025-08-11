#include <stdlib.h>
#include <stdbool.h>

#ifndef __linked_list_stack_h
#define __linked_list_stack_h

typedef const void *Item;
struct StackNode;

struct LinkedListStack {
  struct StackNode *top;
  int size;
};
typedef struct LinkedListStack *Stack;

void Stack_Init(Stack stack);
void Stack_Clear(Stack stack);

void Stack_Push(Stack stack, Item item);
Item Stack_Pop(Stack stack);
Item Stack_Peek(Stack stack);
 int Stack_Size(Stack stack);
bool Stack_IsEmpty(Stack stack);

struct LLStackIterator {
  struct LinkedListStack *stack;
  struct StackNode *cur;
};
typedef struct LLStackIterator *StackIterator;

void StackIterator_Init(StackIterator iterator, Stack stack);
void StackIterator_Clear(StackIterator iterator);
bool StackIterator_HasNext(StackIterator iterator);
Item StackIterator_GetNext(StackIterator iterator);

#endif  // __linked_list_stack_h

