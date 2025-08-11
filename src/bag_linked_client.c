#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bag_linked.h"

#define BUFFER_SIZE 16

/**
 * ### Compile
 * `% mkdir build`
 * `% gcc src/bag_linked_client.c src/bag_linked.c -o build/bag_linked_client.out`
 *
 * ### Run
 *
 * `% more input.txt`
 * `I II III IV V`
 * `% build/bag_linked_client.out < input.txt`
 *
 */
int main() {
  struct LinkedListBag _bag, *bag = &_bag;
  Bag_Init(bag);

  char buffer[BUFFER_SIZE];
  printf("** Bag (Linked List) **\n");
  printf("\n");

  while (fscanf(stdin, "%15s", buffer) != EOF) {
    if (strncmp(buffer, "x\0", 2) == 0) {
      break;
    }

    size_t bufLen = strlen(buffer);
    char *str = calloc(bufLen + 1, sizeof(char));
    snprintf(str, bufLen + 1, "%s", buffer);
    Bag_Add(bag, str);
    printf("add(%s)\n", str);
  }

  printf("\n");
  printf("is_empty() = %s\n", Bag_IsEmpty(bag) ? "true" : "false");
  printf("size() = %d\n", Bag_Size(bag));

  struct LLBagIterator _iterator, *iterator = &_iterator;
  BagIterator_Init(iterator, bag);

  while (BagIterator_HasNext(iterator)) {
    char *str = (char *) BagIterator_GetNext(iterator);
    printf("iterator_next() = %s\n", str);
    free(str), (str = NULL);
  }
  printf("\n");

  BagIterator_Clear(iterator), (iterator = NULL);
  Bag_Clear(bag), (bag = NULL);

  return 0;
}

#undef BUFFER_SIZE

