#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "graph_connected_components.h"
#include "common_macros.h"

struct GraphConnectedComponents {
  Graph graph;
  int vertices;
  bool *marked;
  int *id;
  uint64_t count;
};

static int _dfs(GraphCC graphCC, const int v) {
  if (IS_NULL(graphCC)) { errno = EINVAL; return -1; }
  if (!(0 <= v && v < graphCC->vertices)) { errno = EINVAL; return -1; }

  graphCC->marked[v] = true;
  graphCC->id[v] = graphCC->count;

  AdjVertexIter iterator = AdjVertexIter_Create(graphCC->graph, v);
  if (IS_NULL(iterator)) { return -1; }

  while (AdjVertexIter_HasNext(iterator)) {
    int w;
    int retCode = AdjVertexIter_GetNext(iterator, &w);
    if (retCode != 0) { 
      AdjVertexIter_Free(&iterator);
      return retCode;
    }

    // Visit only unvisted vertices
    if (graphCC->marked[w]) { continue; }
    retCode = _dfs(graphCC, w);

    if (retCode != 0) {
      AdjVertexIter_Free(&iterator);
      return retCode;
    }
  }

  AdjVertexIter_Free(&iterator);
  return 0;
}

GraphCC GraphCC_Create(Graph graph) {
  if (IS_NULL(graph)) { errno = EINVAL; return NULL; }

  GraphCC graphCC = calloc(1, sizeof(*graphCC));
  if (IS_NULL(graphCC)) { errno = ENOMEM; return NULL; }

  const int vertices = Graph_Vertices(graph);

  bool *marked = calloc(vertices, sizeof(*marked));
  if (IS_NULL(marked)) { errno = ENOMEM; return NULL; }

  int *id = calloc(vertices, sizeof(*id));
  if (IS_NULL(id)) { errno = ENOMEM; return NULL; }

  for (int v = 0; v < vertices; v++) {
    id[v] = v;
  }

  graphCC->graph = graph;
  graphCC->vertices = vertices;
  graphCC->marked = marked;
  graphCC->id = id;
  graphCC->count = 0;

  for (int v = 0; v < graphCC->vertices; v++) {
    if (!graphCC->marked[v]) {
      const int retCode = _dfs(graphCC, v);
      graphCC->count++;

      if (retCode != 0) {
        free(marked), (marked = NULL);
        free(id), (id = NULL);
        free(graphCC), (graphCC = NULL);
        return NULL;
      }
    }
  }

  return graphCC;
}

void GraphCC_Free(GraphCC *graphCC) {
  if (IS_NULL(graphCC) || IS_NULL(*graphCC)) { return; }

  if ((*graphCC)->marked) {
    free((*graphCC)->marked), ((*graphCC)->marked = NULL);
  }
  if ((*graphCC)->id) {
    free((*graphCC)->id), ((*graphCC)->id = NULL);
  }
  free(*graphCC), (*graphCC = NULL);
}

bool GraphCC_Connected(const GraphCC graphCC, const int v, const int w) {
  if (!(0 <= v && v < graphCC->vertices) ||
      !(0 <= w && w < graphCC->vertices)) {
    return false;
  }
  return graphCC->id[v] == graphCC->id[w];
}

uint64_t GraphCC_Count(const GraphCC graphCC) {
  return graphCC->count;
}

int GraphCC_Id(const GraphCC graphCC, const int v) {
  return (0 <= v && v < graphCC->vertices) ? graphCC->id[v] : -1;
}

