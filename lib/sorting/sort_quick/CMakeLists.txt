add_library(sort_quick SHARED sort_quick.c)
target_include_directories(sort_quick PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sort_quick PRIVATE sort_insertion)
target_link_libraries(sort_quick PRIVATE std_random)
target_link_libraries(sort_quick PRIVATE arr_utils)

