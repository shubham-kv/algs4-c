add_criterion_test(test_graph test_graph.c)
target_link_libraries(test_graph PRIVATE graph)

add_criterion_test(test_graph_search_dfs test_graph_search_dfs.c)
target_link_libraries(test_graph_search_dfs 
  PRIVATE 
    graph
    graph_search_dfs
)

add_criterion_test(test_graph_search_dfp test_graph_search_dfp.c)
target_link_libraries(test_graph_search_dfp
  PRIVATE 
    graph
    graph_search_dfp
)

add_criterion_test(test_graph_search_bfs test_graph_search_bfs.c)
target_link_libraries(test_graph_search_bfs
  PRIVATE
    graph
    graph_search_bfs
)

add_criterion_test(test_graph_paths_bfp test_graph_paths_bfp.c)
target_link_libraries(test_graph_paths_bfp
  PRIVATE
    graph
    graph_paths_bfp
)

