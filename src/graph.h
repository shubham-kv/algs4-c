#include <stdio.h>
#include <stdbool.h>
#include "bag_linked_int.h"

#ifndef __graph_h
#define __graph_h

struct AdjacencyListGraph {
  /**
   * Array of adjacency lists, vertex indexed array of lists of vertices
   * adjacent to each vertex.
   */
  Bag *adjList;

  /** Number of vertices */
  int V;

  /** Number of edges */
  int E;
};
typedef struct AdjacencyListGraph *Graph;

/**
 * Allocates a `Graph` object on heap. Use `Graph_Init()` to initialize the
 * instance.
 */
Graph Graph_Alloc();

/**
 * De-allocates the memory allocated for `Graph` object on heap, internally uses
 * `Graph_Clear()` before de-allocation.
 */
void Graph_Free(Graph graph);

/** Initialize a V-vertex graph */
void Graph_Init(Graph graph, int V);

/** De-allocate allocated memory for instance variables and clear the memory. */
void Graph_Clear(Graph graph);

/** Number of vertices in the graph */
int Graph_Vertices(Graph graph);

/** Number of edges in the graph */
int Graph_Edges(Graph graph);

/** Add an edge v-w in this graph */
void Graph_AddEdge(Graph graph, int v, int w);

void Graph_Print(Graph graph, FILE *file);


/** Iterator for adjacent vertices of a given vertex `v`. */
struct AdjVertexIterator {
  Graph graph;
  int v;
  BagIterator bagIterator;
};
typedef struct AdjVertexIterator *AdjVerIterator;

#define ITER AdjVerIterator

ITER AdjVerIterator_Alloc();

/** Internally uses `AdjVerIterator_Clear()` before de-allocating the memory */
void AdjVerIterator_Free(ITER iterator);
 int AdjVerIterator_Init(ITER iterator, Graph graph, int v);
void AdjVerIterator_Clear(ITER iterator);
bool AdjVerIterator_HasNext(ITER iterator);
 int AdjVerIterator_GetNext(ITER iterator, int *outV);

#undef ITER

#endif // __graph_h

