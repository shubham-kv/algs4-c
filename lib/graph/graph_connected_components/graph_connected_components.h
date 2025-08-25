#include <stdbool.h>
#include <stdint.h>
#include "graph.h"

#ifndef __graph_connected_components_h
#define __graph_connected_components_h

/** A graph processing struct used to find all the connected components of a
 * given graph. */
struct GraphConnectedComponents;
typedef struct GraphConnectedComponents *GraphCC;

/** Creates a `struct GraphConnectedComponents` object on the heap for the given
 * `graph` and processes the graph to find all the connected components. Use
 * `GraphCC_Free()` to free the allocated memory corresponding to this object. */
GraphCC GraphCC_Create(Graph graph);
void GraphCC_Free(GraphCC *graphCC);

/** Are the given two vertices `v` and `w` connected ? */
bool GraphCC_Connected(const GraphCC graphCC, const int v, const int w);

/** The number of connected components in the graph. */
uint64_t GraphCC_Count(const GraphCC graphCC);

/** Returns the associated component identifier for the given vertex `v`, a
 * value in the range `[0..(GraphCC_Count() - 1)]` on success or `-1` on error. */
int GraphCC_Id(const GraphCC graphCC, const int v);

#endif // __graph_connected_components_h

