cmake_minimum_required(VERSION 3.14)
project(
  "HAF Main Library"
  VERSION 0.8.1.2
  DESCRIPTION "Host Application Framework main library"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX
)

set(_SOURCES main.cpp systemprovider_init.cpp)
file(GLOB_RECURSE _HEADERS "include/*.hpp")

set(CURRENT_TARGET haf)

# Set the public directory for includes in this library. It will be
# used by the external components.
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HAF_PRIVATE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Prepare the haf libray
add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS})
target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_ALLOW_ACCELERATION)
target_compile_definitions(${CURRENT_TARGET} PRIVATE haf_EXPORTS)
set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})

# For now, export all simbols
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                   true)

# External users of the library will need to include from this directory.
target_include_directories(${CURRENT_TARGET}
                           PUBLIC ${HAF_PUBLIC_INCLUDE_DIRECTORY})

# For now, we need it public for tests.
# TODO: Fix it
target_include_directories(${CURRENT_TARGET}
                           PUBLIC ${HAF_PRIVATE_INCLUDE_DIRECTORY})

# target_include_directories( ${CURRENT_TARGET} PUBLIC #
# $<INSTALL_INTERFACE:include> #
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> PRIVATE
# ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_compile_definitions(haf PRIVATE haf_EXPORTS)

include (cmake/haf_functions.cmake)
# Directory internal libraries that will be used by the client too.
add_subdirectory(filesystem)
add_subdirectory(render)
add_subdirectory(resources)
add_subdirectory(scene)
add_subdirectory(scene_components)
add_subdirectory(scene_nodes)
add_subdirectory(time)
add_subdirectory(input)
add_subdirectory(random)
add_subdirectory(simulation)
add_subdirectory(system)
add_subdirectory(shareddata)
add_subdirectory(window)

# Internal libraries necessary for the library only.
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PUBLIC log_and_types)


# TODO: Investigate some day if(MSVC) set_target_properties(${CURRENT_TARGET}
# PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB") endif()

# Build documentation
build_doc(${CURRENT_TARGET})

add_subdirectory(tests)
