#include "graph.h"

#ifndef __graph_search_dfs_h
#define __graph_search_dfs_h

struct DepthFirstSearch;
typedef struct DepthFirstSearch *DFS;

/** Create a DFS object and visit all vertices connected to source vertex `s`
 * using *depth-first-search* algorithm */
DFS DFS_Create(Graph graph, const int s);
void DFS_Free(DFS *dfs);

/** Is v connected to source vertex s? */
bool DFS_Marked(DFS dfs, const int v);

/** How many vertices are connected to s? */
int DFS_Count(DFS dfs);

#endif // __graph_search_dfs_h

