#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "common_macros.h"

/**
 * ### Compile
 * % cmake -S . -B build
 * % make -C build graph_client
 *
 * ### Run
 * % ./build/bin/graph_client < .local/tinyG.txt
 *
 */
int main() {
  FILE *out = stdout;
  fprintf(out, "** Graph (Adjacency Lists) **\n");
  fprintf(out, "\n");

  Graph graph = Graph_CreateFromFile(stdin);

  if (IS_NULL(graph)) {
    fprintf(stderr, "Error creating graph: %s\n", strerror(errno));
    return -1;
  }

  int V = 0, E = 0, code = -1;
  code = Graph_Vertices(graph, &V);
  if (code != 0) { return code; }

  code = Graph_Edges(graph, &E);
  if (code != 0) { return code; }

  fprintf(out, "%d vertices, %d edges\n", V, E);

  for (int vertex = 0; vertex < V; vertex++) {
    fprintf(out, "%d:", vertex);

    AdjVertexIter iter = AdjVertexIter_Create(graph, vertex);

    if (IS_NULL(iter)) {
      fprintf(stderr, "Error creating iterator: %s\n", strerror(errno));
      return -1;
    }

    while (AdjVertexIter_HasNext(iter)) {
      int adjacentVertex;

      if (AdjVertexIter_GetNext(iter, &adjacentVertex) == 0) {
        fprintf(out, " %d", adjacentVertex);
      }
    }
    fprintf(out, "\n");

    AdjVertexIter_Free(&iter);
  }
  fprintf(out, "\n");

  Graph_Free(&graph);

  return 0;
}

