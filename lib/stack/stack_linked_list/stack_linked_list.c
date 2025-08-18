#include <stdlib.h>
#include <memory.h>
#include "stack_linked_list.h"

struct StackNode {
  struct StackNode *next;
  Item data;
};
typedef struct StackNode *Node;

inline void Stack_Init(Stack stack) {
  stack->top = NULL, stack->size = 0;
}

void Stack_Clear(Stack stack) {
  while (!Stack_IsEmpty(stack)) {
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
  if (Stack_IsEmpty(stack)) {
    return NULL;
  }

  Item item = stack->top->data;
  Node next = stack->top->next;
  free(stack->top), (stack->top = NULL);

  stack->top = next;
  stack->size--;
  return item;
}

inline Item Stack_Peek(Stack stack) {
  return Stack_IsEmpty(stack) ? NULL : stack->top->data;
}

inline int Stack_Size(Stack stack) {
  return stack->size;
}

inline bool Stack_IsEmpty(Stack stack) {
  return Stack_Size(stack) == 0;
}


inline void StackIterator_Init(StackIterator iterator, Stack stack) {
  iterator->stack = stack, iterator->cur = iterator->stack->top;
}

inline void StackIterator_Clear(StackIterator iterator) {
  memset(iterator, 0, sizeof(struct LLStackIterator));
}

inline bool StackIterator_HasNext(StackIterator iterator) {
  return iterator->cur != NULL;
}

Item StackIterator_GetNext(StackIterator iterator) {
  if (!StackIterator_HasNext(iterator)) {
    return NULL;
  }

  Item item = iterator->cur->data;
  iterator->cur = iterator->cur->next;

  return item;
}

