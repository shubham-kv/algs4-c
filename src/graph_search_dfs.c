#include <memory.h>
#include <stdlib.h>
#include "graph_search_dfs.h"

static void dfsRecursive(DFS dfs, int v) {
  dfs->visited[v] = true;
  dfs->count++;

  struct AdjVertexIterator _iter, *iter = &_iter;
  AdjVerIterator_Init(iter, dfs->graph, v);

  while (AdjVerIterator_HasNext(iter)) {
    int w;

    if (AdjVerIterator_GetNext(iter, &w) == 0) {
      if (!dfs->visited[w]) {
        dfsRecursive(dfs, w);
      }
    }
  }

  AdjVerIterator_Clear(iter);
}

int DFS_Init(DFS dfs, Graph graph, int s) {
  if (!(0 <= s && s < Graph_Vertices(graph))) {
    return -1;
  }

  dfs->graph = graph;
  dfs->s = s;
  dfs->visited = calloc(Graph_Vertices(graph), sizeof(bool));
  dfs->count = 0;
  dfsRecursive(dfs, s);
  return 0;
}

inline void DFS_Clear(DFS dfs) {
  free(dfs->visited), (dfs->visited = NULL);
  memset(dfs, 0, sizeof(struct DepthFirstSearch));
}

inline bool DFS_Marked(DFS dfs, int v) {
  return dfs->visited[v];
}

inline int DFS_Count(DFS dfs) {
  return dfs->count;
}

