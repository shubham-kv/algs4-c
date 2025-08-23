#include <criterion/criterion.h>
#include "graph.h"
#include "graph_paths_bfp.h"

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
    graph_paths_bfp_has_path_to,
    should_have_path,
    .init = setup,
    .fini = teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 9, 10);

  const int sourceVertex = 0;
  BFP bfp = BFP_Create(graph, sourceVertex);
  cr_assert(BFP_HasPathTo(bfp, 1));
  cr_assert(BFP_HasPathTo(bfp, 2));

  BFP_Free(&bfp);
}

Test(
    graph_paths_bfp_has_path_to,
    should_not_have_path,
    .init = setup,
    .fini = teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 9, 10);

  const int sourceVertex = 0;
  BFP bfp = BFP_Create(graph, sourceVertex);

  cr_assert(!BFP_HasPathTo(bfp, 3));
  cr_assert(!BFP_HasPathTo(bfp, 9));

  BFP_Free(&bfp);
}

Test(
    graph_paths_bfp_vertex_in_path_iter,
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
  BFP bfp = BFP_Create(graph, sourceVertex);
  cr_assert_eq(BFP_HasPathTo(bfp, destVertex), true);

  BFPVertexIter vertexIter = BFPVertexIter_Create(bfp, destVertex);
  cr_assert(vertexIter != NULL);

  int nextVertex, expectedNextVertex;

  expectedNextVertex = 0;
  cr_assert_eq(BFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(BFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_expect(nextVertex == expectedNextVertex,
            "Expected next vertex in path to be %d, got %d", expectedNextVertex,
            nextVertex);

  expectedNextVertex = 1;
  cr_assert_eq(BFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(BFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_expect(nextVertex == expectedNextVertex,
            "Expected next vertex in path to be %d, got %d", expectedNextVertex,
            nextVertex);

  expectedNextVertex = 2;
  cr_assert_eq(BFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(BFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_expect(nextVertex == expectedNextVertex,
            "Expected next vertex in path to be %d, got %d", expectedNextVertex,
            nextVertex);

  expectedNextVertex = 4;
  cr_assert_eq(BFPVertexIter_HasNext(vertexIter), true);
  cr_assert_eq(BFPVertexIter_GetNext(vertexIter, &nextVertex), SUCCESS_RETURN_CODE);
  cr_expect(nextVertex == expectedNextVertex,
            "Expected next vertex in path to be %d, got %d", expectedNextVertex,
            nextVertex);

  cr_assert_eq(BFPVertexIter_HasNext(vertexIter), false);
  cr_assert_eq(BFPVertexIter_GetNext(vertexIter, &nextVertex), ERR_RETURN_CODE);

  BFPVertexIter_Free(&vertexIter);
  BFP_Free(&bfp);
}

