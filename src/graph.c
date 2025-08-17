#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define ITER AdjVerIterator


inline Graph Graph_Alloc() {
  return calloc(1, sizeof(struct AdjacencyListGraph));
}

inline void Graph_Free(Graph graph) {
  Graph_Clear(graph), free(graph), (graph = NULL);
}

void Graph_Init(Graph graph, int V) {
  graph->V = V;
  graph->adjList = calloc(graph->V, sizeof(Bag *));

  for (int i = 0; i < graph->V; i++) {
    Bag bag = Bag_Alloc();
    Bag_Init(bag);
    graph->adjList[i] = bag;
  }

  graph->E = 0;
}

void Graph_Clear(Graph graph) {
  for (int i = 0; i < graph->V; i++) {
    Bag_Free(graph->adjList[i]), (graph->adjList[i] = NULL);
  }
  free(graph->adjList), (graph->adjList = NULL);
  memset(graph, 0, sizeof(struct AdjacencyListGraph));
}

inline int Graph_Vertices(Graph graph) {
  return graph->V;
}

inline int Graph_Edges(Graph graph) {
  return graph->V;
}

void Graph_AddEdge(Graph graph, int v, int w) {
  Bag_Add(graph->adjList[v], w);
  Bag_Add(graph->adjList[w], v);
  graph->E++;
}

void Graph_Print(Graph graph, FILE *file) {
  struct AdjVertexIterator _iter, *iter = &_iter;

  fprintf(file, "%d vertices, %d edges\n", graph->V, graph->E);

  for (int v = 0; v < graph->V; v++) {
    fprintf(file, "%d:", v);
    AdjVerIterator_Init(iter, graph, v);

    while (AdjVerIterator_HasNext(iter)) {
      int adjVertex;
      if (AdjVerIterator_GetNext(iter, &adjVertex) == 0) {
        fprintf(file, " %d", adjVertex);
      }
    }
    AdjVerIterator_Clear(iter);

    fprintf(file, "\n");
  }
}


inline ITER AdjVerIterator_Alloc() {
  return calloc(1, sizeof(struct AdjVertexIterator));
}

inline void AdjVerIterator_Free(ITER iterator) {
  AdjVerIterator_Clear(iterator), free(iterator), (iterator = NULL);
}

int AdjVerIterator_Init(ITER iterator, Graph graph, int v) {
  if (!(0 <= v && v < Graph_Vertices(graph))) {
    return -1;
  }
  iterator->graph = graph;
  iterator->v = v;
  iterator->bagIterator = BagIterator_Alloc();
  BagIterator_Init(iterator->bagIterator, graph->adjList[v]);
  return 0;
}

void AdjVerIterator_Clear(ITER iterator) {
  BagIterator_Free(iterator->bagIterator), (iterator->bagIterator = NULL);
  memset(iterator, 0, sizeof(struct AdjVertexIterator));
}

inline bool AdjVerIterator_HasNext(ITER iterator) {
  return BagIterator_HasNext(iterator->bagIterator);
}

inline int AdjVerIterator_GetNext(ITER iterator, int *outV) {
  return BagIterator_GetNext(iterator->bagIterator, outV);
}

#undef ITER

