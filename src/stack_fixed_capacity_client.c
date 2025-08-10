#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fixed_capacity.h"

#define STACK_CAPACITY 128
#define BUFFER_SIZE 128

/**
 * ### Compile:
 * `% mkdir build`
 * `% gcc src/stack_fixed_capacity_client.c src/stack_fixed_capacity.c -o build/stack_fixed_capacity_client`
 *
 * ### Run:
 * `% ./build/stack_fixed_capacity_client`
 *
 */
int main() {
  uint8_t _stack[FIXED_CAPACITY_STACK_WIDTH];
  Stack stack = (Stack)_stack;
  Stack_Init(stack, STACK_CAPACITY);

  char inputBuffer[BUFFER_SIZE];

  printf("Instructions:\n"
         "1. Enter a string to push to stack\n"
         "2. Enter '-' to pop from stack\n"
         "3. Enter 'x' to break out of input loop\n"
         "\nYour input:\n");

  while (fscanf(stdin, "%127s", inputBuffer) != EOF) {
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
    inputBuffer[0] = '\0';
  }

  printf("(%d left on stack)\n", Stack_Size(stack));
  Stack_Clear(stack);

  return 0;
}

#undef STACK_CAPACITY
#undef BUFFER_SIZE

