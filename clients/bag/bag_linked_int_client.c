#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bag_linked_int.h"

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build
 *
 * ### Run
 * % echo "1 2 3 4 5 x" > input.txt
 * % ./build/bin/bag_linked_int_client < input.txt
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

