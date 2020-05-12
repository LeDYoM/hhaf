cmake_minimum_required(VERSION 3.14)
project(haf)

#include_directories("..")

set(_SOURCES "main.cpp")
file(GLOB_RECURSE _HEADERS "include/*.hpp")

set(CURRENT_TARGET ${PROJECT_NAME})
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)
add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS})
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                   true)

target_include_directories(
  ${CURRENT_TARGET}
  PUBLIC # $<INSTALL_INTERFACE:include>
         # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> PRIVATE
         ${CMAKE_CURRENT_SOURCE_DIR}/../)

# Directory internal libraries that will be used by the client too.
add_subdirectory(filesystem)
target_link_libraries(${CURRENT_TARGET} PRIVATE filesystem)
add_subdirectory(render)
target_link_libraries(${CURRENT_TARGET} PRIVATE render)
add_subdirectory(resources)
target_link_libraries(${CURRENT_TARGET} PRIVATE resources)
add_subdirectory(scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
add_subdirectory(scene_components)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_components)
add_subdirectory(scene_nodes)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_nodes)
add_subdirectory(time)
target_link_libraries(${CURRENT_TARGET} PRIVATE time)
add_subdirectory(input)
target_link_libraries(${CURRENT_TARGET} PRIVATE input)
add_subdirectory(random)
target_link_libraries(${CURRENT_TARGET} PRIVATE random)
add_subdirectory(simulation)
target_link_libraries(${CURRENT_TARGET} PRIVATE simulation)
add_subdirectory(system)
target_link_libraries(${CURRENT_TARGET} PUBLIC system)
add_subdirectory(shareddata)
target_link_libraries(${CURRENT_TARGET} PRIVATE shareddata)
add_subdirectory(window)
target_link_libraries(${CURRENT_TARGET} PRIVATE window)

# Internal libraries necessary for the library only.
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)

add_log_and_types()

# TODO: Investigate some day if(MSVC) set_target_properties(${CURRENT_TARGET}
# PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB") endif()

# first we can indicate the documentation build as an option and set it to ON by
# default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the
  # application
  add_custom_target(
    doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
else(DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)

add_subdirectory(tests)
