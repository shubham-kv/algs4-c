add_library(graph_search_dfs SHARED graph_search_dfs.c)
target_include_directories(graph_search_dfs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(graph_search_dfs PRIVATE graph)

