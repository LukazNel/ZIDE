cmake_minimum_required (VERSION 2.6)
project (ZIDE CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)
