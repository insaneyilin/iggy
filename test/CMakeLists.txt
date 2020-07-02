project(iggy_test)

add_executable(iggy_base_object_pool_test
    iggy_base_object_pool_test.cc)
target_link_libraries(iggy_base_object_pool_test
    iggy_common_time
    gtest gtest_main pthread)

add_executable(iggy_base_signal_slot_test
    iggy_base_signal_slot_test.cc)
target_link_libraries(iggy_base_signal_slot_test
    iggy_common_time
    gtest gtest_main pthread)

add_executable(iggy_base_thread_pool_test
    iggy_base_thread_pool_test.cc)
target_link_libraries(iggy_base_thread_pool_test
    iggy_common_time
    gtest gtest_main pthread)

add_executable(iggy_base_worker_thread_test
    iggy_base_worker_thread_test.cc)
target_link_libraries(iggy_base_worker_thread_test
    iggy_base
    gtest gtest_main pthread)

add_executable(iggy_base_concurrent_queue_test
    iggy_base_concurrent_queue_test.cc)
target_link_libraries(iggy_base_concurrent_queue_test
    iggy_common_time
    gtest gtest_main pthread)

add_executable(iggy_base_bounded_concurrent_queue_test
    iggy_base_bounded_concurrent_queue_test.cc)
target_link_libraries(iggy_base_bounded_concurrent_queue_test
    iggy_common_time
    gtest gtest_main pthread)

add_executable(iggy_common_util_macros_test
    iggy_common_util_macros_test.cc)
target_link_libraries(iggy_common_util_macros_test
    gtest gtest_main pthread)

add_executable(iggy_common_util_string_util_test
    iggy_common_util_string_util_test.cc)
target_link_libraries(iggy_common_util_string_util_test
    iggy_common_util
    gtest gtest_main pthread)

add_executable(iggy_common_util_file_util_test
    iggy_common_util_file_util_test.cc)
target_link_libraries(iggy_common_util_file_util_test
    iggy_common_util
    gtest gtest_main pthread)

add_executable(iggy_common_util_lru_cache_test
    iggy_common_util_lru_cache_test.cc)
target_link_libraries(iggy_common_util_lru_cache_test
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

add_executable(iggy_math_util_angle_test
    iggy_math_util_angle_test.cc)
target_link_libraries(iggy_math_util_angle_test
    iggy_math_util
    gtest gtest_main pthread)

add_executable(iggy_math_util_mean_filter_test
    iggy_math_util_mean_filter_test.cc)
target_link_libraries(iggy_math_util_mean_filter_test
    iggy_math_util
    gtest gtest_main pthread)

add_executable(iggy_math_estimation_kalman_filter_test
    iggy_math_estimation_kalman_filter_test.cc)
target_link_libraries(iggy_math_estimation_kalman_filter_test
    iggy_math_util
    gtest gtest_main pthread)

add_executable(iggy_math_estimation_extended_kalman_filter_test
    iggy_math_estimation_extended_kalman_filter_test.cc)
target_link_libraries(iggy_math_estimation_extended_kalman_filter_test
    iggy_math_util
    gtest gtest_main pthread)

add_executable(iggy_image_proc_io_image_test
    iggy_image_proc_io_image_test.cc)
target_link_libraries(iggy_image_proc_io_image_test
    iggy_image_proc_io
    gtest gtest_main pthread)

add_test(NAME iggy_base_object_pool_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_base_object_pool_test)
add_test(NAME iggy_base_signal_slot_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_base_signal_slot_test)
add_test(NAME iggy_base_thread_pool_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_base_thread_pool_test)
add_test(NAME iggy_base_worker_thread_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_base_worker_thread_test)
add_test(NAME iggy_base_concurrent_queue_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_base_concurrent_queue_test)
add_test(NAME iggy_base_bounded_concurrent_queue_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_base_bounded_concurrent_queue_test)
add_test(NAME iggy_common_util_macros_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_macros_test)
add_test(NAME iggy_common_util_string_util_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_string_util_test)
add_test(NAME iggy_common_util_file_util_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_file_util_test)
add_test(NAME iggy_common_util_lru_cache_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_util_lru_cache_test)
add_test(NAME iggy_common_factory_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_factory_test)
add_test(NAME iggy_common_time_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_common_time_test)
add_test(NAME iggy_math_util_math_util_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_math_util_math_util_test)
add_test(NAME iggy_math_util_angle_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_math_util_angle_test)
add_test(NAME iggy_math_util_mean_filter_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_math_util_mean_filter_test)
add_test(NAME iggy_math_estimation_kalman_filter_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_math_estimation_kalman_filter_test)
add_test(NAME iggy_math_estimation_extended_kalman_filter_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_math_estimation_extended_kalman_filter_test)
add_test(NAME iggy_image_proc_io_image_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/iggy_image_proc_io_image_test)
