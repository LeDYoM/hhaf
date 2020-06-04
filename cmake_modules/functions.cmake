# Function to build different components from the project in an unified way.
function(build_lib_component)

  cmake_parse_arguments(LC_BUILD "EXPORT_ALL" "HEADER_DIRECTORY" "SOURCES"
                        ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})

  if(LC_BUILD_EXPORT_ALL)
    set_target_properties(${CURRENT_TARGET}
                          PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
  endif()

  target_include_directories(${CURRENT_TARGET}
                             PUBLIC ${LC_BUILD_HEADER_DIRECTORY})

endfunction(build_lib_component)

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

endfunction(build_concrete_backend)

function(add_test_executable)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCE_TESTS" ${ARGN})

  include(FetchContent)
  FetchContent_MakeAvailable(Catch2)

  foreach(NAME IN LISTS LC_BUILD_SOURCE_TESTS)
    list(APPEND SOURCE_TESTS_LIST ${NAME}.test.cpp)
  endforeach()

  enable_testing()
  add_executable(${CURRENT_TARGET} ${SOURCE_TESTS_LIST})

  target_link_libraries(${CURRENT_TARGET} PUBLIC Catch2)
  target_include_directories(
    ${CURRENT_TARGET} PRIVATE "${Catch2_SOURCE_DIR}/single_include/catch2")

endfunction(add_test_executable)

function(add_development_dependency _source _dependency)
    add_dependencies(${_source} ${_dependency})
endfunction(add_development_dependency)

function(add_haf_test_executable)

  set(PARAM_LIST ${ARGV})
  list(APPEND PARAM_LIST main)

  add_test_executable(${PARAM_LIST})

  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

endfunction(add_haf_test_executable)

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
