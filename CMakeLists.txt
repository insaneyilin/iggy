cmake_minimum_required(VERSION 3.0)

project(iggy)

include(cmake/options.cmake)
include(cmake/packages.cmake)

add_subdirectory(iggy)

enable_testing()
add_subdirectory(test)
