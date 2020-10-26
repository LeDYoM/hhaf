# Function to build different components from the project in an unified way.
function(build_internal_lib_component)


  cmake_parse_arguments(LC_BUILD "" "INTERNAL_TARGET"
                        "SOURCES;PRIVATE_INTERNAL_LINK" ${ARGN})

  set(CURRENT_TARGET ${LC_BUILD_INTERNAL_TARGET})
  set(_INTERNAL_INCLUDE "/i_include")
  set(_INTERNAL_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}${_INTERNAL_INCLUDE}")
  set(INTERNAL_FOR_OTHERS_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/../")

#  set(MODULE_INCLUDE_FOR_SRC_FILES
#      ${HAF_PUBLIC_INCLUDE_DIRECTORY}haf/${CURRENT_TARGET}/include/)

  # TODO: Add all sources
  target_sources(haf PRIVATE ${extra_file} ${LC_BUILD_SOURCES})
  #add_library(${CURRENT_TARGET} STATIC ${LC_BUILD_SOURCES})
  
  # Add <root>/haf/include/ to all users of haf
  #target_include_directories(${CURRENT_TARGET}
  #                           PUBLIC ${HAF_PUBLIC_INCLUDE_DIRECTORY})

  target_include_directories(haf PUBLIC ${HAF_PUBLIC_INCLUDE_DIRECTORY})

  # Internal includes
  target_include_directories(haf
                             PRIVATE ${_INTERNAL_INCLUDE_DIRECTORY})
  #target_include_directories(${CURRENT_TARGET}
  #                           PRIVATE ${_INTERNAL_INCLUDE_DIRECTORY})

  # Only for this target
  target_include_directories(haf
                             PRIVATE ${MODULE_INCLUDE_FOR_SRC_FILES})
  #target_include_directories(${CURRENT_TARGET}
  #                           PRIVATE ${MODULE_INCLUDE_FOR_SRC_FILES})

  # Add a target to allow internal access to modules. Perhaps that should be
  # temporary
  add_library(${CURRENT_TARGET}_internal INTERFACE)
  target_include_directories(${CURRENT_TARGET}_internal
                             INTERFACE ${INTERNAL_FOR_OTHERS_INCLUDE_DIRECTORY})

#  target_link_libraries(${CURRENT_TARGET} PRIVATE log_and_types)
  target_link_libraries(haf PRIVATE log_and_types)

  # Link all private static internal libraries passed as parameters
  foreach(PRIVATE_LINK IN LISTS LC_BUILD_PRIVATE_INTERNAL_LINK)
    target_link_libraries(haf PRIVATE ${PRIVATE_LINK})
  endforeach()

endfunction(build_internal_lib_component)

# Function to build different components from the project in an unified way.
function(build_concrete_backend)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${SOURCES})

  target_link_libraries(${CURRENT_TARGET} PRIVATE log_and_types)
  target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)

endfunction(build_concrete_backend)
