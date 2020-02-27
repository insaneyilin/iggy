project(iggy_math_util)

aux_source_directory(. IGGY_MATH_UTIL_SRCS)

add_library(${PROJECT_NAME}
  ${IGGY_MATH_UTIL_SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION
    ${CMAKE_INSTALL_PREFIX}/lib/)
