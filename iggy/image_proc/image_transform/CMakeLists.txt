project(iggy_image_proc_image_transform)

aux_source_directory(. IGGY_IMAGE_PROC_IMAGE_TRANSFORM_SRCS)

add_library(${PROJECT_NAME}
        ${IGGY_IMAGE_PROC_IMAGE_TRANSFORM_SRCS})

target_link_libraries(${PROJECT_NAME}
        iggy_image_proc_base iggy_common_util iggy_math_util)

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
