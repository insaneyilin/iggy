project(iggy_common_time)

aux_source_directory(. IGGY_COMMON_TIME_SRCS)

add_library(${PROJECT_NAME}
  ${IGGY_COMMON_TIME_SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
