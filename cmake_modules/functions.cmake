function(build_client_library)

  cmake_parse_arguments(CL_BUILD "" "DATA_SOURCE" "HEADERS;SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} SHARED ${CL_BUILD_SOURCES} ${CL_BUILD_HEADERS})

  set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                     true)

  # Detect and add libraries
  target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

  # Copy data if data directory has been passed.
  if(NOT ${CL_BUILD_DATA_SOURCE} STREQUAL "")
    message(VERBOSE "Post build command. Copy directory")
    message(VERBOSE ${CL_BUILD_DATA_SOURCE})
    message(VERBOSE "to")
    message(VERBOSE $<TARGET_FILE_DIR:${CURRENT_TARGET}>)

    add_custom_command(
      TARGET ${CURRENT_TARGET}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CL_BUILD_DATA_SOURCE}
              $<TARGET_FILE_DIR:${CURRENT_TARGET}>)
  endif()

endfunction(build_client_library)

function(add_log_and_types)
  target_link_libraries(${CURRENT_TARGET} PUBLIC mtypes)
  target_link_libraries(${CURRENT_TARGET} PUBLIC memmanager)
  target_link_libraries(${CURRENT_TARGET} PUBLIC hlog)
endfunction(add_log_and_types)

# Function to build different components from the project in an unified way.
function(build_lib_component)

  cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})

  add_library(${CURRENT_TARGET} SHARED ${LC_BUILD_SOURCES})

  set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                     true)

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

  install(
    TARGETS ${CURRENT_TARGET}
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .)

endfunction(build_lib_interface_component)

# Function to build different components from the project in an unified way.
function(build_internal_lib_component)

  cmake_parse_arguments(LC_BUILD "" "HEADER_DIRECTORY" "SOURCES" ${ARGN})

  set(CURRENT_TARGET ${PROJECT_NAME})
  set(_INTERNAL_INCLUDE "/i_include")
  set(_INTERNAL_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}${_INTERNAL_INCLUDE}")
  set(INTERNAL_FOR_OTHERS_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/../")

  # This variable will point to <root>/haf/include/<module>/include/ it is
  # intended to allow cpp files in the library to use "file.hpp"
  set(MODULE_INCLUDE_FOR_SRC_FILES
      ${HAF_PUBLIC_INCLUDE_DIRECTORY}haf/${CURRENT_TARGET}/include/)

  # TODO: Add all sources
  add_library(${CURRENT_TARGET} STATIC ${LC_BUILD_SOURCES})

  # Add <root>/haf/include/ to all users of haf
  target_include_directories(${CURRENT_TARGET}
                             PUBLIC ${HAF_PUBLIC_INCLUDE_DIRECTORY})

  # Internal includes
  target_include_directories(${CURRENT_TARGET}
                             PRIVATE ${_INTERNAL_INCLUDE_DIRECTORY})

  # Only for this target
  target_include_directories(${CURRENT_TARGET}
                             PRIVATE ${MODULE_INCLUDE_FOR_SRC_FILES})

  # Add a target to allow internal access to modules. Perhaps that should be
  # temporary
  add_library(${CURRENT_TARGET}_internal INTERFACE)
  target_include_directories(${CURRENT_TARGET}_internal
                             INTERFACE ${INTERNAL_FOR_OTHERS_INCLUDE_DIRECTORY})

  add_log_and_types()

endfunction(build_internal_lib_component)

# Function to build different components from the project in an unified way.
function(build_concrete_backend)

  cmake_parse_arguments(LC_BUILD "" "" "SOURCES" ${ARGN})

  add_library(${CURRENT_TARGET} SHARED ${SOURCES})

  add_log_and_types()
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

function(add_haf_test_executable)

  set(PARAM_LIST ${ARGV})
  list(APPEND PARAM_LIST main)

  add_test_executable(${PARAM_LIST})

  target_link_libraries(${CURRENT_TARGET} PRIVATE haf)

endfunction(add_haf_test_executable)
