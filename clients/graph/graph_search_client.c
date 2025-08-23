#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "graph_search_dfs.h"
#include "graph_search_bfs.h"
#include "common_macros.h"

typedef enum SearchAlgorithm {
  DEPTH_FIRST,
  BREADTH_FIRST
} SearchAlgo;

// static const SearchAlgo searchAlgo = DEPTH_FIRST;
static const SearchAlgo searchAlgo = BREADTH_FIRST;

static int _depthFirstSearch(Graph graph, const int sourceVertex);
static int _breadthFirstSearch(Graph graph, const int sourceVertex);
static void _printCliUsage(FILE *file, const char *programName);

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build graph_search_client
 *
 * ### Run
 * % ./build/bin/graph_search_client tinyG.txt 9
 *
 */
int main(int argc, const char *argv[]) {
  if (argc != 3) {
    _printCliUsage(stderr, argv[0]);
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

  int vertices;
  vertices = Graph_Vertices(graph);

  if (!(0 <= sourceVertex && sourceVertex < vertices)) {
    fprintf(stderr, "Error: Invalid source vertex index %d\n", sourceVertex);
    fprintf(stderr, "\n");
    return -1;
  }

  switch (searchAlgo) {
  case DEPTH_FIRST: {
    _depthFirstSearch(graph, sourceVertex);
    break;
  }

  case BREADTH_FIRST: {
    _breadthFirstSearch(graph, sourceVertex);
    break;
  }
  }

  Graph_Free(&graph);
  fclose(file);

  return 0;
}

static int _depthFirstSearch(Graph graph, const int sourceVertex) {
  const int vertices = Graph_Vertices(graph);

  DFS dfs = DFS_Create(graph, sourceVertex);

  if (IS_NULL(dfs)) {
    fprintf(stderr, "Error creating dfs: %s\n", strerror(errno));
    return -1;
  }

  printf("** Depth First Search **\n");

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
  printf("\n");

  DFS_Free(&dfs);
  return 0;
}

static int _breadthFirstSearch(Graph graph, const int sourceVertex) {
  const int vertices = Graph_Vertices(graph);
  BFS bfs = BFS_Create(graph, sourceVertex);

  if (IS_NULL(bfs)) {
    fprintf(stderr, "Error creating bfs: %s\n", strerror(errno));
    return -1;
  }

  printf("** Breadth First Search **\n");

  for (int v = 0; v < vertices; v++) {
    if (BFS_Marked(bfs, v)) {
      printf("%d ", v);
    }
  }
  printf("\n");

  if (BFS_Count(bfs) < vertices) {
    printf("Not connected");
  } else if (BFS_Count(bfs) == vertices) {
    printf("Connected");
  }
  printf("\n");
  printf("\n");

  BFS_Free(&bfs);
  return 0;
}

static void _printCliUsage(FILE *file, const char *programName) {
  fprintf(file, "Usage: %s <file> <s>\n", programName);
  fprintf(file, "\n");
  fprintf(file, "Create a graph from <file> and search for vertices connected "
                "to <s> in the graph.\n");
  fprintf(file, "\n");
  fprintf(file, "%-10s %s\n", "file", "File name used to build the graph");
  fprintf(file, "%-10s %s\n", "s", "Search vertex");
  fprintf(file, "\n");
}
