#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "graph.h"
#include "bag_linked_int.h"
#include "common_macros.h"

struct AdjListsGraph {
  Bag *adjList;
  int vertices;
  int edges;
};

Graph Graph_Create(const int V) {
  Graph graph = calloc(1, sizeof(struct AdjListsGraph));
  if (IS_NULL(graph)) { errno = ENOMEM; return NULL; }

  graph->vertices = V;
  graph->adjList = calloc(V, sizeof(Bag *));
  graph->edges = 0;

  for (int v = 0; v < graph->vertices; v++) {
    Bag bag = Bag_Alloc();
    if (IS_NULL(bag)) { errno = ENOMEM; return NULL; }

    Bag_Init(bag);
    graph->adjList[v] = bag;
  }

  return graph;
}

Graph Graph_CreateFromFile(FILE *file) {
  if (IS_NULL(file)) { errno = EINVAL; return NULL; }

  int vertices = 0, edges = 0;
  fscanf(file, "%d", &vertices);
  fscanf(file, "%d", &edges);

  Graph graph = Graph_Create(vertices);
  if (IS_NULL(graph)) { return NULL; }

  int v = 0, w = 0;

  while (fscanf(file, "%d %d", &v, &w) != EOF) {
    if ((0 <= v && v < vertices) && (0 <= w && w < vertices)) {
      Graph_AddEdge(graph, v, w);
    }
  }

  return graph;
}

void Graph_Free(Graph *graph) {
  if (IS_NULL(graph) || IS_NULL(*graph)) { return; }

  if ((*graph)->adjList) {
    const int vertices = (*graph)->vertices;

    for (int v = 0; v < vertices; v++) {
      Bag_Free((*graph)->adjList[v]), ((*graph)->adjList[v] = NULL);
    }

    free((*graph)->adjList), ((*graph)->adjList = NULL);
  }

  free(*graph), (*graph = NULL);
}

inline int Graph_Vertices(Graph graph) {
  return graph->vertices;
}

inline int Graph_Edges(Graph graph) {
  return graph->edges;
}

void Graph_AddEdge(Graph graph, const int v, const int w) {
  if (IS_NULL(graph)) { errno = EINVAL; return; }
  if (!(0 <= v && v < graph->vertices)) { errno = ERANGE; return; }
  if (!(0 <= w && w < graph->vertices)) { errno = ERANGE; return; }

  Bag_Add(graph->adjList[v], w);
  Bag_Add(graph->adjList[w], v);
  graph->edges++;
}


struct AdjVertexIterator {
  Graph graph;
  int v;
  BagIterator bagIterator;
};

#define ITER AdjVertexIter

ITER AdjVertexIter_Create(Graph graph, const int v) {
  ITER iter = calloc(1, sizeof(struct AdjVertexIterator));
  if (IS_NULL(iter)) { errno = ENOMEM; return NULL; }

  iter->graph = graph;
  iter->v = v;
  iter->bagIterator = BagIterator_Alloc();
  if (IS_NULL(iter->bagIterator)) { errno = ENOMEM; return NULL; }

  BagIterator_Init(iter->bagIterator, graph->adjList[v]);

  return iter;
}

void AdjVertexIter_Free(ITER *iter) {
  if (IS_NULL(iter) || IS_NULL(*iter)) { return; }

  if ((*iter)->bagIterator) {
    BagIterator_Free((*iter)->bagIterator), ((*iter)->bagIterator = NULL);
  }

  free(*iter), (*iter = NULL);
}

inline bool AdjVertexIter_HasNext(ITER iter) {
  return BagIterator_HasNext(iter->bagIterator);
}

inline int AdjVertexIter_GetNext(ITER iter, int *outV) {
  return BagIterator_GetNext(iter->bagIterator, outV);
}

#undef ITER

