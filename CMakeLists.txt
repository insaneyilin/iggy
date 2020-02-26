cmake_minimum_required(VERSION 3.0)

project(iggy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIBRARY_DIRS})

# temp test
add_subdirectory(demo)

enable_testing()
add_subdirectory(test)
