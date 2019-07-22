cmake_minimum_required(VERSION 2.6)
project(make_hex CXX)

set(PROJECT_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})
target_link_libraries(${PROJECT_NAME} zutils)
