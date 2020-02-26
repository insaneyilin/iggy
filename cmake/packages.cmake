list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# GTest
find_package(GTest REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GTEST_INCLUDE_DIRS})

link_directories(
  ${GTEST_LIBRARY_DIRS})
