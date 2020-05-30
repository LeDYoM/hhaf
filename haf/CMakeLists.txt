cmake_minimum_required(VERSION 3.14)
project(
  "HAF Main Library"
  VERSION 0.8.1.2
  DESCRIPTION "Host Application Framework main library"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(_SOURCES main.cpp systemprovider_init.cpp)
file(GLOB_RECURSE _HEADERS "include/*.hpp")

set(CURRENT_TARGET haf)

# Set the public directory for includes in this library. It will be
# used by the external components.
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Prepare the haf libray
add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS})
target_link_libraries(${CURRENT_TARGET} PRIVATE system_internal)

#Create interface library for libraries creating instances of haf
add_library(${CURRENT_TARGET}_instancer INTERFACE)
target_link_libraries(${CURRENT_TARGET}_instancer INTERFACE system)

# For now, export all simbols
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                   true)

# External users of the library will need to include from this directory.
target_include_directories(${CURRENT_TARGET}
                           INTERFACE ${HAF_PUBLIC_INCLUDE_DIRECTORY})

# target_include_directories( ${CURRENT_TARGET} PUBLIC #
# $<INSTALL_INTERFACE:include> #
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> PRIVATE
# ${CMAKE_CURRENT_SOURCE_DIR}/../)

include (cmake/haf_functions.cmake)
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

target_link_libraries(${CURRENT_TARGET} PUBLIC log_and_types)

# TODO: Investigate some day if(MSVC) set_target_properties(${CURRENT_TARGET}
# PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB") endif()

# Build documentation
build_doc(${CURRENT_TARGET})

add_subdirectory(tests)
