add_library(graph_search_dfp SHARED graph_search_dfp.c)
target_include_directories(graph_search_dfp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(graph_search_dfp PRIVATE graph)

