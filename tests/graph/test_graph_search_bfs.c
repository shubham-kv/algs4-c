#include <criterion/criterion.h>
#include "graph.h"
#include "graph_search_bfs.h"

static Graph graph;
static const int VERTICES = 13;

static void _setup() {
  graph = Graph_Create(VERTICES);
}

static void _teardown() {
  Graph_Free(&graph);
}

Test(
    graph_search_bfs_marked,
    marks_all_connected_vertices_as_visited,
    .init = _setup,
    .fini = _teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 1, 3);
  Graph_AddEdge(graph, 2, 4);
  Graph_AddEdge(graph, 2, 5);
  Graph_AddEdge(graph, 9, 10);
  Graph_AddEdge(graph, 9, 11);

  BFS bfs = BFS_Create(graph, 0);
  cr_assert(bfs != NULL);

  cr_assert(BFS_Marked(bfs, 0));
  cr_assert(BFS_Marked(bfs, 1));
  cr_assert(BFS_Marked(bfs, 2));
  cr_assert(BFS_Marked(bfs, 3));
  cr_assert(BFS_Marked(bfs, 4));
  cr_assert(BFS_Marked(bfs, 5));

  cr_expect(!BFS_Marked(bfs, 9));
  cr_expect(!BFS_Marked(bfs, 10));
  cr_expect(!BFS_Marked(bfs, 11));

  BFS_Free(&bfs);
}

Test(
    graph_search_bfs_count,
    counts_all_connected_vertices,
    .init = _setup,
    .fini = _teardown
) {
  Graph_AddEdge(graph, 0, 1);
  Graph_AddEdge(graph, 1, 2);
  Graph_AddEdge(graph, 1, 3);
  Graph_AddEdge(graph, 9, 10);
  Graph_AddEdge(graph, 9, 11);

  BFS bfs = BFS_Create(graph, 0);
  cr_assert(bfs != NULL);
  cr_assert_eq(BFS_Count(bfs), 4);

  BFS_Free(&bfs);
}

