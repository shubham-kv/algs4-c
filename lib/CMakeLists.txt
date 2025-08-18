file(GLOB CHILD_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(dir ${CHILD_DIRS})
  if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
    add_subdirectory(${dir})
  endif()
endforeach()

add_library(std_random SHARED std_random.c)
add_library(arr_utils SHARED arr_utils.c)

