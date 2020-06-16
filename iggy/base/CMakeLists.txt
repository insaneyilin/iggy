project(iggy_base)

aux_source_directory(. IGGY_BASE_SRCS)

add_library(${PROJECT_NAME}
        ${IGGY_BASE_SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
