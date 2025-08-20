#include <criterion/criterion.h>
#include "graph.h"
#include "graph_search_dfp.h"

static Graph graph;
static const int VERTICES = 13;

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

  const int sourceVetex = 0;
  DFP dfp = DFP_Create(graph, sourceVetex);
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

  const int sourceVetex = 0;
  DFP dfp = DFP_Create(graph, sourceVetex);

  cr_assert(!DFP_HasPathTo(dfp, 3));
  cr_assert(!DFP_HasPathTo(dfp, 9));

  DFP_Free(&dfp);
}

// TODO: add tests for pathTo()

