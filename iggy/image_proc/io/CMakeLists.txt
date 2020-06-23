project(iggy_image_proc_io)

aux_source_directory(. IGGY_IMAGE_PROC_IO_SRCS)

add_library(${PROJECT_NAME}
        ${IGGY_IMAGE_PROC_IO_SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
