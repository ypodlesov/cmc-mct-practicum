cmake_minimum_required(VERSION 3.14)
project(cmc_mct_practicum)

set(CMAKE_CXX_STANDARD             20)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/tools/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

find_package(Catch REQUIRED)

include_directories(tools/commons)
include(tools/cmake/TestSolution.cmake)
include(tools/cmake/BuildFlags.cmake)

set(Clang_DIR "/usr/lib/llvm-16/lib/cmake/clang")
set(LLVM_DIR "/usr/lib/llvm-16/lib/cmake/llvm")
find_package(Clang CONFIG)

function(add_if_exists name)
  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name})
    add_subdirectory(${name})
  endif()
endfunction()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")

add_if_exists(task_1_solve_eq)