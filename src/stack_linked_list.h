#include <stdlib.h>
#include <stdbool.h>

#ifndef __linked_list_stack_h
#define __linked_list_stack_h

struct StackNode;
struct LinkedListStack;
typedef struct LinkedListStack *Stack;

typedef const void *Item;

struct StackNode {
  struct StackNode *next;
  Item data;
};

struct LinkedListStack {
  struct StackNode *top;
  int size;
};

void Stack_Init(Stack stack);
void Stack_Clear(Stack stack);

void Stack_Push(Stack stack, Item item);
Item Stack_Pop(Stack stack);
 int Stack_Size(Stack stack);
bool Stack_IsEmpty(Stack stack);

#define STACK_SIZE(stack) (((Stack) stack)->size)
#define IS_STACK_EMPTY(stack) (((Stack) stack)->top == NULL)

#endif  // __linked_list_stack_h

