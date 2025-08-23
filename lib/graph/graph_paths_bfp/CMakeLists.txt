add_library(graph_paths_bfp SHARED graph_paths_bfp.c)

target_include_directories(graph_paths_bfp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(graph_paths_bfp
  PRIVATE
    graph
    queue_int
)

