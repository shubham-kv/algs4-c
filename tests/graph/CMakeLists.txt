add_criterion_test(test_graph test_graph.c)
target_link_libraries(test_graph PRIVATE graph)

add_criterion_test(test_graph_search_dfs test_graph_search_dfs.c)
target_link_libraries(test_graph_search_dfs 
  PRIVATE 
    graph
    graph_search_dfs
)

