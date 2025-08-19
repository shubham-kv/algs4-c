#include <criterion/criterion.h>
#include <errno.h>
#include "graph.h"

static Graph graph;
static const int VERTICES = 13;

static void setup() {
  graph = Graph_Create(VERTICES);
}

static void teardown() {
  Graph_Free(&graph);
}

Test(
    graph_vertices,
    returns_correct_number_of_vertices,
    .init = setup,
    .fini = teardown
) {
  int v = Graph_Vertices(graph);
  cr_assert(v == VERTICES, "Expected %d vertices got %d", VERTICES, v);
}

Test(
    graph_edges,
    returns_correct_number_of_edges,
    .init = setup,
    .fini = teardown
) {
  int expectedEdges = 0;
  Graph_AddEdge(graph, 0, 1), (expectedEdges++);
  Graph_AddEdge(graph, 1, 2), (expectedEdges++);

  int edges = Graph_Edges(graph);
  cr_assert(edges == expectedEdges, "Expected %d edge(s) got %d", expectedEdges, edges);
}

Test(
    graph_add_edge,
    adds_edge,
    .init = setup,
    .fini = teardown
) {
  int v = 0, w = 5, code;
  Graph_AddEdge(graph, v, w);

  AdjVertexIter iter;
  int adjacentVertex;

  iter = AdjVertexIter_Create(graph, v);
  code = AdjVertexIter_GetNext(iter, &adjacentVertex);
  cr_expect(code == 0, "AdjVertexIter_GetNext failed with %d", code);
  cr_assert(adjacentVertex == w);
  AdjVertexIter_Free(&iter);

  iter = AdjVertexIter_Create(graph, w);
  code = AdjVertexIter_GetNext(iter, &adjacentVertex);
  cr_expect(code == 0, "AdjVertexIter_GetNext failed with %d", code);
  cr_assert(adjacentVertex == v);
  AdjVertexIter_Free(&iter);
}

