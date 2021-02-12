function(set_cxx_standard CURRENT_TARGET)
    set_property(TARGET ${CURRENT_TARGET} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${CURRENT_TARGET} PROPERTY CXX_STANDARD_REQUIRED ON)
    set_property(TARGET ${CURRENT_TARGET} PROPERTY CXX_EXTENSIONS ON)
    set_property(TARGET ${CURRENT_TARGET} PROPERTY POSITION_INDEPENDENT_CODE ON)       
endfunction()

macro(set_install_dir)
#  set(CMAKE_INSTALL_PREFIX /home/ismael/h_test/)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/phaf/")
  message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
endmacro()

# Function to build different components from the project in an unified way.
function(build_lib_component)

  cmake_parse_arguments(LC_BUILD "EXPORT_ALL;STATIC" "HEADER_DIRECTORY" "SOURCES"
                        ${ARGN})

  if(LC_BUILD_STATIC)
    message(STATUS "Add library static: ${CURRENT_TARGET}")
    add_library(${CURRENT_TARGET} STATIC ${LC_BUILD_SOURCES})
  else()
    message(STATUS "Add library shared: ${CURRENT_TARGET}")
    add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})
  endif()

  set_cxx_standard(${CURRENT_TARGET})

  if(LC_BUILD_EXPORT_ALL)
    if (LC_BUILD_STATIC)
      message(WARN "STATIC and EXPORT_ALL together make no sense")
    endif()
    set_target_properties(${CURRENT_TARGET}
                          PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
  endif()

  if (NOT LC_BUILD_STATIC)
    set_property(TARGET ${CURRENT} PROPERTY POSITION_INDEPENDENT_CODE ON)
  endif()
  
  target_include_directories(${CURRENT_TARGET}
      PUBLIC
      "$<BUILD_INTERFACE:${LC_BUILD_HEADER_DIRECTORY}>"
      "$<INSTALL_INTERFACE:include>"
  )

  include(GNUInstallDirs)
  install(TARGETS ${CURRENT_TARGET}
      EXPORT ${CURRENT_TARGET}Targets
      INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

#  install(EXPORT ${CURRENT_TARGET}Targets
#    FILE ${CURRENT_TARGET}Targets.cmake
#    NAMESPACE hhaf::
#  DESTINATION
#    ${CMAKE_INSTALL_LIBDIR}/cmake/hhaf)

endfunction()

function(build_lib_ext)

  cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})

  set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                     true)

  target_include_directories(${CURRENT_TARGET}
                             PUBLIC ${LC_BUILD_HEADER_DIRECTORY})
  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

endfunction(build_lib_ext)

# Function to build different components from the project in an unified way.
function(build_lib_interface_component)

  cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} INTERFACE)
  target_include_directories(${CURRENT_TARGET}
                             INTERFACE ${LC_BUILD_HEADER_DIRECTORY})

endfunction(build_lib_interface_component)

# Function to build different components from the project in an unified way.
function(build_concrete_backend)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${SOURCES})
  target_link_libraries(${CURRENT_TARGET} PRIVATE log_and_types)
  target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
  target_link_libraries(${CURRENT_TARGET} PRIVATE backend_client)

endfunction(build_concrete_backend)

function(add_development_dependency _source _dependency)
    add_dependencies(${_source} ${_dependency})
endfunction(add_development_dependency)

function(build_doc _base_name)
  # check if Doxygen is installed
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    message("Doxygen found")
    message("Generating doxygen files for " ${_base_name})
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(
      ${_base_name}_doc_doxygen
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen for ${_base_name}"
      VERBATIM)
  else(DOXYGEN_FOUND)
    message(
      "Doxygen need to be installed to generate the doxygen documentation for "
      ${_base_name})
  endif(DOXYGEN_FOUND)
endfunction(build_doc)
