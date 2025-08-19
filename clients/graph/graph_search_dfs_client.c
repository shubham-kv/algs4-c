#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "graph_search_dfs.h"
#include "common_macros.h"

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build graph_client
 *
 * ### Run
 * % build/graph_search_dfs_client.out tinyG.txt 9
 *
 */
int main(int argc, const char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <file> <s>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "Create a graph from <file> and search for vertices connected to <s> in the graph.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "%-10s %s\n", "file", "File name used to build the graph");
    fprintf(stderr, "%-10s %s\n", "s", "Search vertex");
    fprintf(stderr, "\n");
    return -1;
  }

  const char *fileName = argv[1];
  int sourceVertex;
  sscanf(argv[2], "%d", &sourceVertex);

  FILE *file = fopen(fileName, "r");
  if (IS_NULL(file)) {
    fprintf(stderr, "Error reading file '%s': %s\n", fileName, strerror(errno));
    fprintf(stderr, "\n");
    return -1;
  }

  Graph graph = Graph_CreateFromFile(file);
  if (IS_NULL(graph)) {
    fprintf(stderr, "Error creating graph: %s\n", strerror(errno));
    return -1;
  }

  int vertices = 0, code;
  code = Graph_Vertices(graph, &vertices);
  if (code != 0) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return -1;
  }

  if (!(0 <= sourceVertex && sourceVertex < vertices)) {
    fprintf(stderr, "Error: Invalid source vertex index %d\n", sourceVertex);
    fprintf(stderr, "\n");
    return -1;
  }

  DFS dfs = DFS_Create(graph, sourceVertex);
  if (IS_NULL(dfs)) {
    fprintf(stderr, "Error creating dfs: %s\n", strerror(errno));
    return -1;
  }

  for (int v = 0; v < vertices; v++) {
    if (DFS_Marked(dfs, v)) {
      printf("%d ", v);
    }
  }
  printf("\n");

  if (DFS_Count(dfs) < vertices) {
    printf("Not connected");
  } else if (DFS_Count(dfs) == vertices) {
    printf("Connected");
  }
  printf("\n");

  DFS_Free(&dfs);
  Graph_Free(&graph);

  return 0;
}

