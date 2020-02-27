list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# GTest
find_package(GTest REQUIRED)

# Eigen3
find_package(Eigen3 REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${EIGEN3_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIRS})

link_directories(
  ${GTEST_LIBRARY_DIRS})
