#include "graph.h"

#ifndef __depth_first_search
#define __depth_first_search

struct DepthFirstSearch {
  /** The graph to search in */
  Graph graph;

  /** Source vertex to find vertices connected to it */
  int s;

  /** Vertex indexed boolean array for visited vertices */
  bool *visited;

  /** Count of vertices connected to s */
  int count;
};

typedef struct DepthFirstSearch *DFS;

int DFS_Init(DFS dfs, Graph graph, int s);
void DFS_Clear(DFS dfs);

/** Is v connected to source vertex s ? */
bool DFS_Marked(DFS dfs, int v);

/** How many vertices are connected to s? */
int DFS_Count(DFS dfs);

#endif // __depth_first_search

