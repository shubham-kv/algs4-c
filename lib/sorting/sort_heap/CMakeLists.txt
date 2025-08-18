add_library(sort_heap SHARED sort_heap.c)
target_include_directories(sort_heap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sort_heap PRIVATE arr_utils)

