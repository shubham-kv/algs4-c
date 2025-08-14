#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_quick.h"

int charCmp(const void *a, const void *b);
void printChars(char *str, size_t n);

/**
 * ### Compile:
 * % mkdir build
 * % gcc -Wall -g src/sort_quick_client.c src/sort_quick.c \
 *     src/std_random.c src/sort_insertion.c \
 *     -o build/sort_quick_client.out
 *
 * ### Run:
 * `% build/sort_quick_client.out`
 *
 */
int main() {
  char str[] = "sortexample";
  size_t n = strlen(str);

  printf("** Quick Sort **\n");
  printf("Before: ");
  printChars(str, n);
  printf("\n");

  quickSort(str, sizeof(char), n, charCmp);

  printf(" After: ");
  printChars(str, n);
  printf("\n");
  printf("\n");

  return 0;
}

int charCmp(const void *a, const void *b) {
  char c1 = *(const char *)a;
  char c2 = *(const char *)b;
  return c1 < c2 ? -1 : c1 > c2 ? 1 : 0;
}

void printChars(char *str, size_t n) {
  printf("{ '%c'", str[0]);
  for (size_t i = 1; i < n; i++) {
    printf(", '%c'", str[i]);
  }
  printf(" }");
}

