add_library(sort_selection SHARED sort_selection.c)
target_include_directories(sort_selection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sort_selection PRIVATE arr_utils)

