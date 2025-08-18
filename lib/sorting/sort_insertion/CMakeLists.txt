add_library(sort_insertion SHARED sort_insertion.c)
target_include_directories(sort_insertion PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sort_insertion PRIVATE arr_utils)

