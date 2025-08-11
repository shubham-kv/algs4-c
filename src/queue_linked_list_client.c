#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_linked_list.h"

#define BUFFER_SIZE 16

/**
 * ### Compile
 * `% mkdir build`
 * `% gcc src/queue_linked_list_client.c src/queue_linked_list.c -o build/queue_linked_list_client.out`
 *
 * ### Run
 *
 * `% more input.txt`
 * `I II III IV - V -`
 * `% build/queue_linked_list_client.out < input.txt`
 *
 */
int main() {
  struct LinkedListQueue _queue, *queue = &_queue;
  Queue_Init(queue);

  char inputBuffer[BUFFER_SIZE];

  printf("** Queue (Linked List) **\n");
  printf("\n");

  while (fscanf(stdin, "%15s", inputBuffer) != EOF) {
    if (strncmp(inputBuffer, "x\0", 2) == 0) {
      break;
    }

    if (strncmp(inputBuffer, "-\0", 2) == 0) {
      if (!Queue_IsEmpty(queue)) {
        char *str = (char *) Queue_Dequeue(queue);
        printf("dequeue() = %s\n", str);
        free(str), (str = NULL);
      } else {
        printf("Queue is empty!\n");
      }
    } else {
      size_t bufLen = strlen(inputBuffer);
      char *input = calloc(bufLen + 1, sizeof(char));
      snprintf(input, bufLen + 1, "%s", inputBuffer);
      Queue_Enqueue(queue, input);
      printf("enqueue(%s)\n", input);
    }
  }

  printf("\n");
  printf("peek() = %s\n", (char *) Queue_Peek(queue));
  printf("size() = %d\n", Queue_Size(queue));

  struct LLQueueIterator _iterator, *iterator = &_iterator;
  QueueIterator_Init(iterator, queue);

  while (QueueIterator_HasNext(iterator)) {
    const char *str = QueueIterator_GetNext(iterator);
    printf("iterator_next() = %s\n", str);
  }
  printf("\n");

  QueueIterator_Clear(iterator), (iterator = NULL);

  while (!Queue_IsEmpty(queue)) {
    free((char *) Queue_Dequeue(queue));
  }
  Queue_Clear(queue), (queue = NULL);

  return 0;
}

