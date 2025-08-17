#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/**
 * ### Compile
 *
 * % make build
 * % gcc -Wall -g src/graph_client.c \            
 *     src/graph.c \
 *     src/bag_linked_int.c \
 *     -o build/graph_client.out
 *
 * ### Run
 *
 * % build/graph_client.out < tinyG.txt
 *
 */
int main() {
  printf("** Graph (Adjacency Lists) **\n");

  int vertices, edges;
  fscanf(stdin, "%d", &vertices);
  fscanf(stdin, "%d", &edges);

  struct AdjacencyListGraph _graph, *graph = &_graph;
  Graph_Init(graph, vertices);

  int v = 0, w = 0;

  while (fscanf(stdin, "%d %d", &v, &w) != EOF) {
    if (getchar() == 'x') {
      break;
    }

    if ((0 <= v && v < vertices) && (0 <= w && w < vertices)) {
      Graph_AddEdge(graph, v, w);
      printf("add_edge(%d, %d)\n", v, w);
    }
  }
  printf("\n");

  Graph_Print(graph, stdout);
  Graph_Clear(graph), (graph = NULL);

  return 0;
}

