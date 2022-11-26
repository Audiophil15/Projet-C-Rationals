cmake_minimum_required(VERSION 3.10)

project(Rationals VERSION 0.1)

set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_subdirectory(src)
add_subdirectory(test)