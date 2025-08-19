cmake_minimum_required(VERSION 4.1)
project(algs4_c LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable testing
include(CTest)
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

# Helper function to simplify test setup
function(add_criterion_test name)
  add_executable(${name} ${ARGN})

  target_include_directories(${name} PRIVATE ${CRITERION_INCLUDE_DIRS})
  target_link_directories(${name} PRIVATE ${CRITERION_LIBRARY_DIRS})
  target_link_libraries(${name} PRIVATE ${CRITERION_LIBRARIES})
  target_link_options(${name} PRIVATE ${CRITERION_LDFLAGS_OTHER})

  add_test(NAME ${name} COMMAND ${name})
endfunction()

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(lib)
add_subdirectory(clients)
add_subdirectory(tests)

