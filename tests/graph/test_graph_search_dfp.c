#include <criterion/criterion.h>
#include "graph.h"
#include "graph_search_dfp.h"

static Graph graph;
static const int VERTICES = 13;
static const int SUCCESS_RETURN_CODE = 0;
static const int ERR_RETURN_CODE = -1;

static void setup() {
  graph = Graph_Create(VERTICES);
  cr_assert(graph != NULL);
}

static void teardown() {
  Graph_Free(&graph);
}

Test(
    graph_search_dfp_has_path_to,
    should_have_path,
    .init = setup,
    .fini = teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 9, 10);

  const int sourceVertex = 0;
  DFP dfp = DFP_Create(graph, sourceVertex);
  cr_assert(DFP_HasPathTo(dfp, 1));
  cr_assert(DFP_HasPathTo(dfp, 2));

  DFP_Free(&dfp);
}

Test(
    graph_search_dfp_has_path_to,
    should_not_have_path,
    .init = setup,
    .fini = teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 9, 10);

  const int sourceVertex = 0;
  DFP dfp = DFP_Create(graph, sourceVertex);

  cr_assert(!DFP_HasPathTo(dfp, 3));
  cr_assert(!DFP_HasPathTo(dfp, 9));

  DFP_Free(&dfp);
}

Test(
    graph_search_dfp_vertex_in_path_iter,
    should_yield_every_vertex_in_path,
    .init = setup,
    .fini = teardown
) {
  // Graph (2 components)
  //
  // 0 -- 1 -- 2 -- 3
  //      |    |
  //      5    4
  //
  // 9 -- 10
  // |
  // 11
  //

  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 1, 5);
  Graph_AddEdge(graph, 2, 3);
  Graph_AddEdge(graph, 2, 4);
  Graph_AddEdge(graph, 9, 10);
  Graph_AddEdge(graph, 9, 11);

  const int sourceVertex = 0, destVertex = 4;
  DFP dfp = DFP_Create(graph, sourceVertex);
  cr_assert_eq(DFP_HasPathTo(dfp, destVertex), true);

  DFPVertexIter vertexIter = DFPVertexIter_Create(dfp, destVertex);
  cr_assert(vertexIter != NULL);
  int nextVertex;

  cr_assert_eq(DFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(DFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_assert_eq(nextVertex, 0);

  cr_assert_eq(DFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(DFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_assert_eq(nextVertex, 1);

  cr_assert_eq(DFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(DFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_assert_eq(nextVertex, 2);

  cr_assert_eq(DFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(DFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_assert_eq(nextVertex, 4);

  cr_assert_eq(DFPVertexIter_HasNext(vertexIter), false);
  cr_assert_eq(DFPVertexIter_GetNext(vertexIter, &nextVertex), ERR_RETURN_CODE);

  DFPVertexIter_Free(&vertexIter);
  DFP_Free(&dfp);
}

