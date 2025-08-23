#include <stdbool.h>
#include "graph.h"

#ifndef __graph_search_bfs_h
#define __graph_search_bfs_h

/** Graph processing data structure meant to use *breadth first search*
 * algorithm to find all connected vertices to a given source vertex `s`. */
struct BreadthFirstSearch;
typedef struct BreadthFirstSearch *BFS;

/** Creates a `struct BreadthFirstSearch` object on the heap, processes the
 * given `graph` to find all connected vertices to source vertex `s` by using
 * *breadth first search* algorithm and returns a pointer to the allocated
 * memory. Use `BFS_Free` to free the allocated memory. */
BFS BFS_Create(Graph graph, const int s);
void BFS_Free(BFS *bfs);

/** Is `v` connected to the source vertex `s` ? */
bool BFS_Marked(BFS bfs, const int v);

/** How many vertices are connected to source vertex `s`? */
size_t BFS_Count(BFS bfs);

#endif //  __graph_search_bfs_h

