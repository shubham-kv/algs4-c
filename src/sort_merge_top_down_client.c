#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_merge_top_down.h"

int charCmp(const void *a, const void *b);
void printChars(char *str, size_t n);

/**
 * ### Compile:
 * % mkdir build
 * % gcc -Wall -g src/sort_merge_top_down_client.c src/sort_merge_top_down.c src/sort_insertion.c -o build/sort_merge_top_down_client.out
 *
 * ### Run:
 * `% build/sort_merge_top_down_client.out`
 *
 */
int main() {
  char str[] = "sortexample";
  size_t n = strlen(str);

  printf("** Merge Sort (Top Down) **\n");
  printf("Before: ");
  printChars(str, n);
  printf("\n");

  topDownMergeSort(str, sizeof(char), n, charCmp);

  printf(" After: ");
  printChars(str, n);
  printf("\n");
  printf("\n");
}

int charCmp(const void *a, const void *b) {
  char c1 = *(const char *)a;
  char c2 = *(const char *)b;
  return (c1 < c2) ? -1 : (c1 > c2) ? 1 : 0;
}

void printChars(char *str, size_t n) {
  printf("{ '%c'", str[0]);
  for (size_t i = 1; i < n; i++) {
    printf(", '%c'", str[i]);
  }
  printf(" }");
}

