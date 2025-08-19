#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifndef __graph_h
#define __graph_h

/** Adjacency Lists Graph */
struct AdjListsGraph;
typedef struct AdjListsGraph *Graph;

/** Create a V-vertex graph */
Graph Graph_Create(const int V);
Graph Graph_CreateFromFile(FILE *file);
void Graph_Free(Graph *graph);

/** Number of vertices in the graph */
int Graph_Vertices(Graph graph);

/** Number of edges in the graph */
int Graph_Edges(Graph graph);

/** Add an edge v-w in this graph */
void Graph_AddEdge(Graph graph, const int v, const int w);


/** Iterator for iterating over adjacent vertices of a given vertex `v` */
struct AdjVertexIterator;
typedef struct AdjVertexIterator *AdjVertexIter;

#define ITER AdjVertexIter

/** Creates the iterator to iterate over all adjacent vertices of the given vertex `v` */
ITER AdjVertexIter_Create(Graph graph, const int v);
void AdjVertexIter_Free(ITER *iter);
bool AdjVertexIter_HasNext(ITER iter);
 int AdjVertexIter_GetNext(ITER iter, int *outV);

#undef ITER

#endif // __graph_h

