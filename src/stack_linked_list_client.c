#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_linked_list.h"

#define BUFFER_SIZE 60

/**
 * ### Compile:
 * `% mkdir build`
 * `% gcc src/stack_linked_list_client.c src/stack_linked_list.c -o build/stack_linked_list_client.out`
 *
 * ### Run:
 * `% ./build/stack_linked_list_client.out`
 *
 */
int main() {
  struct LinkedListStack _stack, *stack = &_stack;
  Stack_Init(stack);

  char inputBuffer[BUFFER_SIZE];

  printf("** Stack (Linked List) **\n\n"
         "Instructions:\n"
         "1. Enter a string to push to stack\n"
         "2. Enter '-' to pop from stack\n"
         "3. Enter 'x' to break out of input loop\n"
         "\nYour input:\n");

  while (fscanf(stdin, "%59s", inputBuffer) != EOF) {
    if (strncmp(inputBuffer, "x\0", 2) == 0) {
      break;
    }

    if (strncmp(inputBuffer, "-\0", 2) == 0) {
      if (Stack_Size(stack) > 0) {
        char *popped = (char *) Stack_Pop(stack);
        printf("%s\n", popped);
        free(popped);
      } else {
        printf("Stack is empty\n");
      }
    }
    else {
      size_t bufLen = strlen(inputBuffer);
      char *input = calloc(bufLen + 1, sizeof(char));
      snprintf(input, bufLen + 1, "%s", inputBuffer);
      Stack_Push(stack, input);
    }
  }

  printf("\n");
  printf("peek() = %s\n", (char *) Stack_Peek(stack));
  printf("(%d left on stack)\n", Stack_Size(stack));

  struct LLStackIterator _iterator, *iterator = &_iterator;
  StackIterator_Init(iterator, stack);

  while (StackIterator_HasNext(iterator)) {
    char *input = (char *) StackIterator_GetNext(iterator);
    printf("%s\n", input);
  }

  StackIterator_Clear(iterator), (iterator = NULL);

  while (!Stack_IsEmpty(stack)) {
    free((char *) Stack_Pop(stack));
  }
  Stack_Clear(stack), (stack = NULL);

  return 0;
}

#undef BUFFER_SIZE

