# Function to build different components from the project in an unified way.
function(build_concrete_backend)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})
  target_link_libraries(${CURRENT_TARGET} PRIVATE
    log_and_types
    backend_dev
    backend_client)
endfunction()
