project(iggy_common_util)

aux_source_directory(. IGGY_COMMON_UTIL_SRCS)

add_library(${PROJECT_NAME}
  ${IGGY_COMMON_UTIL_SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
