#include <errno.h>
#include <stdlib.h>
#include "graph_search_dfp.h"
#include "common_macros.h"

struct DepthFirstPaths {
  Graph graph;
  int graphVertices;

  // TODO: Check if `sourceVertex` is still needed
  int sourceVertex;
  bool *marked;
  int *edgeTo;
  int count;
};

#define ITER DFPVertexIter

static void _dfpRecursive(DFP dfp, const int v) {
  if (IS_NULL(dfp)) { return; }
  if (!(0 <= v && v < dfp->graphVertices)) { return; }

  dfp->marked[v] = true;
  dfp->count++;

  AdjVertexIter iterator = AdjVertexIter_Create(dfp->graph, v);

  while (AdjVertexIter_HasNext(iterator)) {
    int w;
    if (AdjVertexIter_GetNext(iterator, &w) == 0) {
      if (!dfp->marked[w]) {
        dfp->edgeTo[w] = v;
        _dfpRecursive(dfp, w);
      }
    }
  }

  AdjVertexIter_Free(&iterator);
}

DFP DFP_Create(Graph graph, const int s) {
  if (IS_NULL(graph)) { errno = EINVAL; return NULL; }

  const int vertices = Graph_Vertices(graph);
  if (!(0 <= s && s < vertices)) { errno = ERANGE; return NULL; }

  DFP dfp = calloc(1, sizeof(struct DepthFirstPaths));
  if (IS_NULL(dfp)) { errno = ENOMEM; return NULL; }

  dfp->graph = graph;
  dfp->graphVertices = vertices;
  dfp->sourceVertex = s;
  dfp->count = 0;

  dfp->marked = calloc(dfp->graphVertices, sizeof(bool));
  if (IS_NULL(dfp->marked)) { errno = ENOMEM; return NULL; }

  dfp->edgeTo  = calloc(dfp->graphVertices, sizeof(int));
  if (IS_NULL(dfp->edgeTo)) { errno = ENOMEM; return NULL; }

  _dfpRecursive(dfp, dfp->sourceVertex);

  return dfp;
}

void DFP_Free(DFP *dfp) {
  if (IS_NULL(dfp) || IS_NULL(*dfp)) { return; }

  if ((*dfp)->marked) {
    free((*dfp)->marked), ((*dfp)->marked = NULL);
  }

  if ((*dfp)->edgeTo) {
    free((*dfp)->edgeTo), ((*dfp)->edgeTo = NULL);
  }

  free(*dfp), (*dfp = NULL);
}

inline bool DFP_HasPathTo(DFP dfp, const int v) {
  return dfp->marked[v];
}

// TODO: implement vertex in a path iterator
ITER DFPVertexIter_Create(DFP dfp, const int v);
void DFPVertexIter_Free(ITER iterator);
bool DFPVertexIter_HasNext(ITER iterator);
 int DFPVertexIter_GetNext(ITER iterator);

#undef ITER

