#include <errno.h>
#include <stdlib.h>
#include "graph_search_dfp.h"
#include "common_macros.h"

struct DepthFirstPaths {
  Graph graph;
  int graphVertices;
  int sourceVertex;
  bool *marked;
  int *edgeTo;
  int count;
};

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

  dfp->edgeTo = calloc(dfp->graphVertices, sizeof(int));
  if (IS_NULL(dfp->edgeTo)) { errno = ENOMEM; return NULL; }

  for (int i = 0; i < dfp->graphVertices; i++) {
    dfp->edgeTo[i] = -1;
  }

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

struct DFPVertexIterator {
  int *verticesStack;
  int stackSize;
  int i;
};

#define ITER DFPVertexIter

ITER DFPVertexIter_Create(DFP dfp, const int v) {
  if (IS_NULL(dfp)) { errno = EINVAL; return NULL; }
  if (!(0 <= v && v < dfp->graphVertices)) { errno = ERANGE; return NULL; }
  if (!DFP_HasPathTo(dfp, v)) { errno = EINVAL; return NULL; }

  ITER iter = calloc(1, sizeof(struct DFPVertexIterator));
  if (IS_NULL(iter)) { errno = ENOMEM; return NULL; }

  int *verticesStack = calloc(dfp->graphVertices, sizeof(int));
  if (IS_NULL(verticesStack)) { errno = ENOMEM; return NULL; }

  int stackSize = 0;

  for (int w = v; w >= 0; w = dfp->edgeTo[w]) {
    verticesStack[stackSize++] = w;
  }

  iter->verticesStack = verticesStack;
  iter->stackSize = stackSize;
  iter->i = iter->stackSize - 1;

  return iter;
}

void DFPVertexIter_Free(ITER *iterator) {
  if (IS_NULL(iterator) || IS_NULL(*iterator)) { return; }

  if ((*iterator)->verticesStack) {
    free((*iterator)->verticesStack), ((*iterator)->verticesStack = NULL);
  }

  free(*iterator), (*iterator = NULL);
}

inline bool DFPVertexIter_HasNext(ITER iterator) {
  return iterator->i >= 0;
}

inline int DFPVertexIter_GetNext(ITER iterator, int *out) {
  if (IS_NULL(iterator)) { errno = EINVAL; return -1; }
  if (!DFPVertexIter_HasNext(iterator)) { errno = ENODATA; return -1; }

  *out = iterator->verticesStack[iterator->i];
  iterator->i--;
  return 0;
}

#undef ITER

