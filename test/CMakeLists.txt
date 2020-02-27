project(iggy_test)

add_executable(iggy_common_util_macros_test
    iggy_common_util_macros_test.cc)
target_link_libraries(iggy_common_util_macros_test
    gtest gtest_main pthread)

add_executable(iggy_common_util_string_util_test
    iggy_common_util_string_util_test.cc)
target_link_libraries(iggy_common_util_string_util_test
    iggy_common_util
    gtest gtest_main pthread)

add_executable(iggy_common_factory_test
    iggy_common_factory_test.cc)
target_link_libraries(iggy_common_factory_test
    iggy_common_factory
    gtest gtest_main pthread)

add_executable(iggy_common_time_test
    iggy_common_time_test.cc)
target_link_libraries(iggy_common_time_test
    iggy_common_time
    gtest gtest_main pthread)

add_executable(iggy_math_util_math_util_test
    iggy_math_util_math_util_test.cc)
target_link_libraries(iggy_math_util_math_util_test
    iggy_math_util
    gtest gtest_main pthread)

add_test(NAME iggy_common_util_macros_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_macros_test)
add_test(NAME iggy_common_util_string_util_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_string_util_test)
add_test(NAME iggy_common_factory_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_factory_test)
add_test(NAME iggy_common_time_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_time_test)
add_test(NAME iggy_math_util_math_util_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_math_util_math_util_test)
