file(GLOB CHILD_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(dir ${CHILD_DIRS})
  if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
    add_subdirectory(${dir})
  endif()
endforeach()

add_library(std_random SHARED std_random.c)
target_include_directories(std_random PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
