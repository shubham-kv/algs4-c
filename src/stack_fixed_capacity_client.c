#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fixed_capacity.h"

#define STACK_CAPACITY 8
#define BUFFER_SIZE 60

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
  struct FixedCapacityStack _stack, *stack = &_stack;
  Stack_Init(stack, STACK_CAPACITY);

  char inputBuffer[BUFFER_SIZE];

  printf(
    "** Stack (Fixed Capacity of %d) **\n\n"
    "Instructions:\n"
    "1. Enter a string to push to stack\n"
    "2. Enter '-' to pop from stack\n"
    "3. Enter 'x' to break out of input loop\n"
    "\nYour input:\n", STACK_CAPACITY);

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
      if (Stack_Size(stack) < STACK_CAPACITY) {
        size_t bufLen = strlen(inputBuffer);
        char *input = calloc(bufLen + 1, sizeof(char));
        snprintf(input, bufLen + 1, "%s", inputBuffer);
        Stack_Push(stack, input);

        if (Stack_Size(stack) == STACK_CAPACITY) {
          printf("Stack is full\n");
        }
      } else {
        printf("Stack is full\n");
      }
    }
    inputBuffer[0] = '\0';
  }

  printf("(%d left on stack)\n", Stack_Size(stack));
  Stack_Clear(stack);

  return 0;
}

#undef STACK_CAPACITY
#undef BUFFER_SIZE

