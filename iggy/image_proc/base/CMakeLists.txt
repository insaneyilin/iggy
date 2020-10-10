project(iggy_image_proc_base)

aux_source_directory(. IGGY_IMAGE_PROC_BASE_SRCS)

add_library(${PROJECT_NAME}
        ${IGGY_IMAGE_PROC_BASE_SRCS})

target_link_libraries(${PROJECT_NAME} iggy_common_util)

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
