#include <criterion/criterion.h>
#include "graph.h"
#include "graph_connected_components.h"
#include "common_macros.h"

static Graph graph;
static const int VERTICES = 9;
static const int SUCCESS_RETURN_CODE = 0;
static const int ERR_RETURN_CODE = -1;

static void setup() {
  graph = Graph_Create(VERTICES);
  cr_assert(graph != NULL);

  // Graph (2 components)
  //
  // 0 -- 1 -- 2 -- 3
  //      |    |
  //      5    4
  //
  // 6 -- 7
  // |
  // 8
  //

  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 1, 5);
  Graph_AddEdge(graph, 2, 3);
  Graph_AddEdge(graph, 2, 4);
  Graph_AddEdge(graph, 6, 7);
  Graph_AddEdge(graph, 6, 8);
}

static void teardown() {
  Graph_Free(&graph);
}

Test(
    graph_CC_connected,
    should_return_true_for_connected_vertices_false_otherwise,
    .init = setup,
    .fini = teardown
) {
  GraphCC graphCC = GraphCC_Create(graph);
  cr_assert(graphCC != NULL);

  const int connectedVertices[][2] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
    {1, 1}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
    {2, 2}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5},
    {3, 3}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5},
    {4, 4}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5},
    {5, 5}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5},
    {6, 6}, {6, 7}, {6, 8},
    {7, 6}, {7, 7}, {7, 8},
    {8, 6}, {8, 7}, {8, 8},
  };
  const int connectedVerticesCount =
      sizeof(connectedVertices) / sizeof(connectedVertices[0]);

  for (int i = 0; i < connectedVerticesCount; i++) {
    int v, w;
    bool expected, actual;

    v = connectedVertices[i][0], w = connectedVertices[i][1];
    expected = true, actual = GraphCC_Connected(graphCC, v, w);
    cr_expect_eq(actual, expected,
                 "For vertices %d and %d, expected connected query to return %s, got %s",
                 v, w, BOOL_TO_STRING(expected), BOOL_TO_STRING(actual));
  }

  const int nonConnectedVertices[][2] = {
    {0, 6}, {0, 7}, {0, 8},
    {1, 6}, {1, 7}, {1, 8},
    {2, 6}, {2, 7}, {2, 8},
    {3, 6}, {3, 7}, {3, 8},
    {4, 6}, {4, 7}, {4, 8},
    {5, 6}, {5, 7}, {5, 8},
  };
  const int nonConnectedVerticesCount =
      sizeof(nonConnectedVertices) / sizeof(nonConnectedVertices[0]);

  for (int i = 0; i < nonConnectedVerticesCount; i++) {
    int v, w;
    bool expected, actual;

    v = nonConnectedVertices[i][0], w = nonConnectedVertices[i][1];
    expected = false, actual = GraphCC_Connected(graphCC, v, w);
    cr_expect_eq(actual, expected,
                 "For vertices %d and %d, expected connected query to return %s, got %s",
                 v, w, BOOL_TO_STRING(expected), BOOL_TO_STRING(actual));
  }

  GraphCC_Free(&graphCC);
}

Test(
    graph_CC_count,
    should_correctly_count_connected_components,
    .init = setup,
    .fini = teardown
) {
  GraphCC graphCC = GraphCC_Create(graph);
  cr_assert(graphCC);

  const int expected = 2;
  const int actual = GraphCC_Count(graphCC);
  cr_assert_eq(actual, expected,
               "Expected number of connected components to be %d, got %d",
               expected, actual);

  GraphCC_Free(&graphCC);
}

Test(
    graph_CC_id,
    returned_ids_should_be_in_range,
    .init = setup,
    .fini = teardown
) {
  GraphCC graphCC = GraphCC_Create(graph);
  cr_assert(graphCC);

  for (int v = 0; v < VERTICES; v++) {
    const int componentId = GraphCC_Id(graphCC, v);

    cr_assert(0 <= componentId && componentId < VERTICES,
              "Expected component id for vertex %d to be in range [0..%d], got %d",
              v, VERTICES - 1, componentId);
  }

  GraphCC_Free(&graphCC);
}

