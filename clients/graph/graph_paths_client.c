#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "graph_search_dfp.h"
#include "graph_paths_bfp.h"
#include "common_macros.h"

enum PathFindingAlgorithm {
  DEPTH_FIRST,
  BREADTH_FIRST
};

static int _depthFirstPaths(Graph graph, const int sourceVertex);
static int _breadthFirstPaths(Graph graph, const int sourceVertex);
static void _printCLIUsage(FILE *file, const char *binaryName);

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build graph_paths_client
 *
 * ### Run
 * % ./build/bin/graph_paths_client dfs .local/tinyG.txt 0
 * 
 */
int main(const int argc, const char *argv[]) {
  if (argc != 4) {
    _printCLIUsage(stderr, argv[0]);
    return -1;
  }

  enum PathFindingAlgorithm pathFindingAlgorithm;
  const char *algoArg = argv[1];

  if (strncmp(algoArg, "dfs", 3) == 0) {
    pathFindingAlgorithm = DEPTH_FIRST;
  } else if (strncmp(algoArg, "bfs", 3) == 0) {
    pathFindingAlgorithm = BREADTH_FIRST;
  } else {
    fprintf(stderr, "Error: Invalid <algo> argument received, expected 'dfs' or 'bfs', got '%s'\n", algoArg);
    fprintf(stderr, "\n");
    return -1;
  }

  const char *fileName = argv[2];
  int sourceVertex = -1;
  sscanf(argv[3], "%d", &sourceVertex);

  FILE *file = fopen(fileName, "r");
  if (IS_NULL(file)) {
    fprintf(stderr, "Error opening file '%s': %s\n", fileName, strerror(errno));
    fprintf(stderr, "\n");
    return -1;
  }

  Graph graph = Graph_CreateFromFile(file);
  fclose(file), (file = NULL);

  if (IS_NULL(graph)) {
    fprintf(stderr, "Error creating graph: %s\n", strerror(errno));
    fprintf(stderr, "\n");
    return -1;
  }

  const int nOfVertices = Graph_Vertices(graph);

  if (!(0 <= sourceVertex && sourceVertex < nOfVertices)) {
    fprintf(stderr, "Error: Expected given source vertex to be in range [0..%d], got %d\n", nOfVertices, sourceVertex);
    fprintf(stderr, "\n");
    Graph_Free(&graph);
    return -1;
  }

  switch (pathFindingAlgorithm) {
  case DEPTH_FIRST: {
    const int code = _depthFirstPaths(graph, sourceVertex);
    graph = NULL;

    if (code != 0) { return code; }
    break;
  }
  case BREADTH_FIRST: {
    const int code = _breadthFirstPaths(graph, sourceVertex);
    graph = NULL;

    if (code != 0) { return code; }
    break;
  }
  }

  return 0;
}

static int _depthFirstPaths(Graph graph, const int sourceVertex) {
  const int nOfVertices = Graph_Vertices(graph);

  DFP dfp = DFP_Create(graph, sourceVertex);
  if (IS_NULL(dfp)) {
    fprintf(stderr, "Error processing the graph: %s\n", strerror(errno));
    fprintf(stderr, "\n");
    Graph_Free(&graph);
    return -1;
  }

  printf("** Depth First Paths **\n");

  for (int v = 0; v < nOfVertices; v++) {
    if (!DFP_HasPathTo(dfp, v)) {
      continue;
    }

    DFPVertexIter pathVertexIterator = DFPVertexIter_Create(dfp, v);
    if (IS_NULL(pathVertexIterator)) {
      fprintf(stderr, "Error processing the graph: %s\n", strerror(errno));
      fprintf(stderr, "\n");
      Graph_Free(&graph);
      return -1;
    }

    printf("%d to %d: ", sourceVertex, v);

    while (DFPVertexIter_HasNext(pathVertexIterator)) {
      int w;
      if (DFPVertexIter_GetNext(pathVertexIterator, &w) == 0) {
        if (w != sourceVertex) {
          printf("-%d", w);
        } else {
          printf("%d", w);
        }
      }
    }
    printf("\n");

    DFPVertexIter_Free(&pathVertexIterator);
  }
  printf("\n");

  DFP_Free(&dfp);
  Graph_Free(&graph);
  return 0;
}

static int _breadthFirstPaths(Graph graph, const int sourceVertex) {
  const int nOfVertices = Graph_Vertices(graph);

  BFP bfp = BFP_Create(graph, sourceVertex);
  if (IS_NULL(bfp)) {
    fprintf(stderr, "Error processing the graph: %s\n", strerror(errno));
    fprintf(stderr, "\n");
    Graph_Free(&graph);
    return -1;
  }

  printf("** Breadth First Paths **\n");

  for (int v = 0; v < nOfVertices; v++) {
    if (!BFP_HasPathTo(bfp, v)) {
      continue;
    }

    BFPVertexIter pathVertexIterator = BFPVertexIter_Create(bfp, v);
    if (IS_NULL(pathVertexIterator)) {
      fprintf(stderr, "Error processing the graph: %s\n", strerror(errno));
      fprintf(stderr, "\n");
      Graph_Free(&graph);
      return -1;
    }

    printf("%d to %d: ", sourceVertex, v);

    while (BFPVertexIter_HasNext(pathVertexIterator)) {
      int w;
      if (BFPVertexIter_GetNext(pathVertexIterator, &w) == 0) {
        if (w != sourceVertex) {
          printf("-%d", w);
        } else {
          printf("%d", w);
        }
      }
    }
    printf("\n");

    BFPVertexIter_Free(&pathVertexIterator);
  }
  printf("\n");

  BFP_Free(&bfp);
  Graph_Free(&graph);
  return 0;
}

static void _printCLIUsage(FILE *file, const char *programName) {
  fprintf(file, "Usage: %s <algo> <file> <s>\n", programName);
  fprintf(file, "\n");
  fprintf(file, "Create a graph from <file> and find all paths from source "
                "vertex <s> to every connected vertex in the graph using the given path finding algorithm <algo>.\n");
  fprintf(file, "\n");
  fprintf(file, "%-10s %s\n", "algo", "Path finding algorithm to use. Either 'dfs' for depth first search or 'bfs' for breadth first search.");
  fprintf(file, "%-10s %s\n", "file", "File name used to build the graph");
  fprintf(file, "%-10s %s\n", "s", "Source vertex");
  fprintf(file, "\n");
}

