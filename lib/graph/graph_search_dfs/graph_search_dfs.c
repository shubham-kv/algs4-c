#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph_search_dfs.h"
#include "common_macros.h"

struct DepthFirstSearch {
  Graph graph;
  int graphVertices;
  int sourceVertex;
  bool *marked;
  int count;
};

static void _dfsRecursive(DFS dfs, const int v) {
  if (IS_NULL(dfs)) { return; }
  if (!(0 <= v && v < dfs->graphVertices)) { return; }

  dfs->marked[v] = true;
  dfs->count++;

  AdjVertexIter iterator = AdjVertexIter_Create(dfs->graph, v);
  if (IS_NULL(iterator)) { return; }

  while (AdjVertexIter_HasNext(iterator)) {
    int w;
    if (AdjVertexIter_GetNext(iterator, &w) == 0) {
      if (!dfs->marked[w]) {
        _dfsRecursive(dfs, w);
      }
    }
  }

  AdjVertexIter_Free(&iterator);
}

DFS DFS_Create(Graph graph, const int s) {
  if (IS_NULL(graph)) { errno = EINVAL; return NULL; }

  int code = -1, vertices = 0;
  code = Graph_Vertices(graph, &vertices);
  if (code != 0) { return NULL; }

  if (!(0 <= s && s < vertices)) { errno = EINVAL; return NULL; }

  DFS dfs = calloc(1, sizeof(struct DepthFirstSearch));
  if (IS_NULL(dfs)) { errno = ENOMEM; return NULL; }

  dfs->graph = graph;
  dfs->sourceVertex = s;
  dfs->graphVertices = vertices;
  dfs->count = 0;

  dfs->marked = calloc(dfs->graphVertices, sizeof(bool));
  if (IS_NULL(dfs->marked)) { errno = ENOMEM; return NULL; }

  _dfsRecursive(dfs, dfs->sourceVertex);

  return dfs;
}

void DFS_Free(DFS *dfs) {
  if (IS_NULL(dfs) || IS_NULL(*dfs)) { return; }

  if ((*dfs)->marked) {
    free((*dfs)->marked), ((*dfs)->marked = NULL);
  }
  free(*dfs), (*dfs = NULL);
}

inline bool DFS_Marked(DFS dfs, const int v) {
  return dfs->marked[v];
}

inline int DFS_Count(DFS dfs) {
  return dfs->count;
}

