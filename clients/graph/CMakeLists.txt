add_executable(graph_client graph_client.c)
target_link_libraries(graph_client PRIVATE graph)

add_executable(graph_search_client graph_search_client.c)
target_link_libraries(graph_search_client
  PRIVATE
    graph
    graph_search_dfs
    graph_search_bfs
)

