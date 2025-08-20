#include <stdbool.h>
#include "graph.h"

#ifndef __graph_search_dfp_h
#define __graph_search_dfp_h

/** Graph processing data structure to find paths to every connected vertex from
 * a source vertex `s` by using *depth first search* algorithm. */
struct DepthFirstPaths;
typedef struct DepthFirstPaths *DFP;

/** Creates a `struct DepthFirstPaths` instance, processes the graph to find
 * paths and returns the instance ptr. */
DFP DFP_Create(Graph graph, const int s);
void DFP_Free(DFP *dfp);
bool DFP_HasPathTo(DFP dfp, const int v);

/** Iterator to sequentially yield every vertex in the path (if a path exists)
 * from source vertex `s` to the given vertex `v` constructed by the `struct
 * DepthFirstPaths` instance. */
struct DFPVertexIterator;
typedef struct DFPVertexIterator *DFPVertexIter;

#define ITER DFPVertexIter

ITER DFPVertexIter_Create(DFP dfp, const int v);
void DFPVertexIter_Free(ITER iterator);
bool DFPVertexIter_HasNext(ITER iterator);
 int DFPVertexIter_GetNext(ITER iterator);

#undef ITER

#endif // __graph_search_dfp_h

