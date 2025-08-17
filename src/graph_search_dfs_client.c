#include <stdio.h>
#include <stdlib.h>
#include "graph_search_dfs.h"

/**
 * ### Compile
 *
 * % make build
 * % gcc -Wall -g src/graph_search_dfs_client.c \            
 *     src/graph_search_dfs.c \
 *     src/graph.c \
 *     src/bag_linked_int.c \
 *     -o build/graph_search_dfs_client.out
 *
 * ### Run
 *
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

  if (file == NULL) {
    fprintf(stderr, "Error: Failed to read file '%s'\n", fileName);
    fprintf(stderr, "\n");
    return -1;
  }

  int vertices, edges;
  fscanf(file, "%d", &vertices);
  fscanf(file, "%d", &edges);

  struct AdjacencyListGraph _graph, *graph = &_graph;
  Graph_Init(graph, vertices);

  int v = 0, w = 0;

  while (fscanf(file, "%d %d", &v, &w) != EOF) {
    if ((0 <= v && v < vertices) && (0 <= w && w < vertices)) {
      Graph_AddEdge(graph, v, w);
    }
  }

  if (!(0 <= sourceVertex && sourceVertex < Graph_Vertices(graph))) {
    Graph_Clear(graph), (graph = NULL);
    fprintf(stderr, "Error: Invalid source vertex index %d\n", sourceVertex);
    fprintf(stderr, "\n");
    return -1;
  }

  struct DepthFirstSearch _dfs, *dfs = &_dfs;

  if (DFS_Init(dfs, graph, sourceVertex) != 0) {
    return -1;
  }

  const int V = Graph_Vertices(graph);

  for (int v = 0; v < V; v++) {
    if (DFS_Marked(dfs, v)) {
      printf("%d ", v);
    }
  }
  printf("\n");

  if (DFS_Count(dfs) != V) {
    printf("Not ");
  }
  printf("Connected\n");

  DFS_Clear(dfs), (dfs = NULL);
  Graph_Clear(graph), (graph = NULL);

  return 0;
}

