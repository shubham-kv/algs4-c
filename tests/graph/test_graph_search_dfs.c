#include <criterion/criterion.h>
#include "graph.h"
#include "graph_search_dfs.h"

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
    graph_search_dfs_count,
    sets_count_correctly_to_all_connected_vertices,
    .init = setup,
    .fini = teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 2, 3);
  Graph_AddEdge(graph, 0, 4);
  Graph_AddEdge(graph, 9, 10);
  Graph_AddEdge(graph, 9, 11);

  const int sourceVertex = 1;
  DFS dfs = DFS_Create(graph, sourceVertex);
  cr_assert(DFS_Count(dfs) == 5);

  DFS_Free(&dfs);
}

Test(
    graph_search_dfs_marked,
    visits_all_connected_vertices,
    .init = setup,
    .fini = teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 2, 3);
  Graph_AddEdge(graph, 0, 4);
  Graph_AddEdge(graph, 9, 10);
  Graph_AddEdge(graph, 9, 11);

  const int sourceVertex = 1;
  DFS dfs = DFS_Create(graph, sourceVertex);

  cr_assert(DFS_Marked(dfs, 0));
  cr_assert(DFS_Marked(dfs, 1));
  cr_assert(DFS_Marked(dfs, 2));
  cr_assert(DFS_Marked(dfs, 3));
  cr_assert(DFS_Marked(dfs, 4));

  cr_assert(!DFS_Marked(dfs, 9));
  cr_assert(!DFS_Marked(dfs, 10));
  cr_assert(!DFS_Marked(dfs, 11));

  DFS_Free(&dfs);
}

