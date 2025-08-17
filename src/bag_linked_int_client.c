#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bag_linked_int.h"

/**
 * ### Compile
 * % mkdir build
 * % gcc -Wall -g src/bag_linked_int_client.c \
 *     src/bag_linked_int.c \
 *     -o build/bag_linked_int_client.out
 *
 * ### Run
 *
 * % more input.txt
 *   10 20 30 40 50 55 68 90
 * % build/bag_linked_int_client.out < input.txt
 *
 */
int main() {
  struct LLIntBag _bag, *bag = &_bag;
  Bag_Init(bag);

  printf("** Bag of integers (Linked List) **\n");
  printf("\n");

  int input;

  while (fscanf(stdin, "%d", &input) != EOF) {
    if (getchar() == 'x') {
      break;
    }

    Bag_Add(bag, input);
    printf("add(%d)\n", input);
  }

  printf("\n");
  printf("is_empty() = %s\n", Bag_IsEmpty(bag) ? "true" : "false");
  printf("size() = %d\n", Bag_Size(bag));

  struct LLIntBagIterator _iterator, *iterator = &_iterator;
  BagIterator_Init(iterator, bag);

  while (BagIterator_HasNext(iterator)) {
    int data;
    int retVal = BagIterator_GetNext(iterator, &data);
    if (retVal != 0) {
      fprintf(stderr, "BagIterator_GetNext returned error value!");
      return retVal;
    }
    printf("iterator_next() = %d\n", data);
  }
  printf("\n");

  BagIterator_Clear(iterator), (iterator = NULL);
  Bag_Clear(bag), (bag = NULL);

  return 0;
}

