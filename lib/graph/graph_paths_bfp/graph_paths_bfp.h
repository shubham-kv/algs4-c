#include <stdbool.h>
#include "graph.h"

#ifndef __graph_paths_bfp_h
#define __graph_paths_bfp_h

/** Struct for graph processing to find paths using *breath first search* graph
 * algorithm. */
struct BreadthFirstPaths;
typedef struct BreadthFirstPaths *BFP;

/** Creates a `struct BreadthFirstPaths` object on the heap & processes the
 * given `graph` to find paths from source vertex `s` to every connected vertex.
 * Use `BFP_Free` to free the allocated memory. */
BFP BFP_Create(Graph graph, const int s);
void BFP_Free(BFP *bfp);

/** Is there a path from the source vertex `s` to the given vertex `v`? */
bool BFP_HasPathTo(BFP bfp, const int v);


/** Iterator to sequentially yield every vertex in the path (if a path exists)
 * from source vertex `s` to the given vertex `v` constructed by the `struct
 * BreadthFirstPaths` object. */
struct BFPVertexIterator;
typedef struct BFPVertexIterator *BFPVertexIter;

#define ITER BFPVertexIter

/** Creates an iterator to iterate over all vertices in the path from source
 * vertex `s` to given vertex `v`. */
ITER BFPVertexIter_Create(BFP dfp, const int v);
void BFPVertexIter_Free(ITER *iterator);

/** Is there a next vertex ? Expects `iterator` to be non-null crashes otherwise. */
bool BFPVertexIter_HasNext(ITER iterator);

/** Sets `vertex` out parameter to the next vertex in the path if there is one
 * and returns `0` otherwise sets `errno` and returns `-1`. */
int BFPVertexIter_GetNext(ITER iterator, int *vertex);

#undef ITER

#endif // __graph_paths_bfp_h

