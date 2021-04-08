# Function to build different components from the project in an unified way.
function(build_internal_lib_component)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  set(_INTERNAL_INCLUDE "/i_include")
  set(_INTERNAL_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}${_INTERNAL_INCLUDE}")
  set(INTERNAL_FOR_OTHERS_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/../")

  # Add the sources of this directory (passed as parameter)
  target_sources(haf PRIVATE ${extra_file} ${LC_BUILD_SOURCES})
  
  # Internal includes
  target_include_directories(haf
                             PRIVATE ${_INTERNAL_INCLUDE_DIRECTORY})

endfunction()

# Function to build different components from the project in an unified way.
function(build_concrete_backend)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${SOURCES})

  target_link_libraries(${CURRENT_TARGET} PRIVATE log_and_types)
  target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

endfunction(build_concrete_backend)
