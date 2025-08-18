add_library(sort_shell SHARED sort_shell.c)
target_include_directories(sort_shell PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sort_shell PRIVATE arr_utils)

