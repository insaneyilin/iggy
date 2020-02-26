project(iggy_test)

add_executable(iggy_common_util_macros_test
    iggy_common_util_macros_test.cc)
target_link_libraries(iggy_common_util_macros_test
    gtest gtest_main pthread)

add_executable(iggy_common_factory_test
    iggy_common_factory_test.cc)
target_link_libraries(iggy_common_factory_test
    iggy_common_factory
    gtest gtest_main pthread)

add_test(NAME iggy_common_util_macros_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_macros_test)
add_test(NAME iggy_common_factory_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_factory_test)
