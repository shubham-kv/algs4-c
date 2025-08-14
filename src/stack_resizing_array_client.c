#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_resizing_array.h"

#define BUFFER_SIZE 128

/**
 * ### Compile:
 * `% mkdir build`
 * `% gcc src/stack_resizing_array_client.c src/stack_resizing_array.c -o build/stack_resizing_array_client`
 *
 * ### Run:
 * `% ./build/stack_resizing_array_client`
 *
 */
int main() {
  struct ResizingArrayStack _stack, *stack = &_stack;
  Stack_Init(stack);

  char inputBuffer[BUFFER_SIZE];

  printf("** Stack (Resizing Array) **\n");
  printf("\n");

  while (fscanf(stdin, "%127s", inputBuffer) != EOF) {
    if (strncmp(inputBuffer, "x\0", 2) == 0) {
      break;
    }

    if (strncmp(inputBuffer, "-\0", 2) == 0) {
      if (Stack_Size(stack) > 0) {
        char *popped = (char *) Stack_Pop(stack);
        printf("pop() = %s\n", popped);
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
      printf("push(%s)\n", input);
    }
  }

  printf("\n");
  printf("peek() = %s\n", (char *) Stack_Peek(stack));
  printf("size() = %d\n", Stack_Size(stack));

  struct RAStackIterator _iterator, *iterator = &_iterator;
  StackIterator_Init(iterator, stack);

  while (StackIterator_HasNext(iterator)) {
    char *popped = (char *) StackIterator_GetNext(iterator);
    printf("iterator_next() = %s\n", popped);
  }
  printf("\n");

  StackIterator_Clear(iterator), (iterator = NULL);

  while (!Stack_IsEmpty(stack)) {
    free((char *) Stack_Pop(stack));
  }
  Stack_Clear(stack), (stack = NULL);

  return 0;
}

#undef BUFFER_SIZE

