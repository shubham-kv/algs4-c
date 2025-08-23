add_library(graph_search_bfs SHARED graph_search_bfs.c)

target_include_directories(graph_search_bfs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(graph_search_bfs
  PRIVATE
    graph
    queue_int
)

