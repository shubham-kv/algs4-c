#include <stdlib.h>
#include "stack_linked_list.h"

typedef struct StackNode *Node;

void Stack_Init(Stack stack) {
  stack->top = NULL;
  stack->size = 0;
}

void Stack_Clear(Stack stack) {
  while (!IS_STACK_EMPTY(stack)) {
    Stack_Pop(stack);
  }
}

void Stack_Push(Stack stack, Item item) {
  Node node = calloc(1, sizeof(struct StackNode));
  node->data = item;
  node->next = stack->top;
  stack->top = node;
  stack->size++;
}

Item Stack_Pop(Stack stack) {
  if (IS_STACK_EMPTY(stack)) {
    return NULL;
  }

  Item item = stack->top->data;
  Node next = stack->top->next;
  free(stack->top), (stack->top = NULL);

  stack->top = next;
  stack->size--;
  return item;
}

inline int Stack_Size(Stack stack) {
  return STACK_SIZE(stack);
}

inline bool Stack_IsEmpty(Stack stack) {
  return IS_STACK_EMPTY(stack);
}

