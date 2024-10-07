cmake_minimum_required(VERSION 3.14)
project(
  "HAF Main Library"
  VERSION 0.8.2.1
  DESCRIPTION "Host Application Framework main library"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX
)

set(CURRENT_TARGET haf)

set(src_dir src)
file (GLOB_RECURSE sources
  ${src_dir}/*.cpp
  ${src_dir}/*.hpp)


set(inc_dir include/haf/include)
file (GLOB_RECURSE headers "${inc_dir}/*.hpp")

# Set the public directory for includes in this library. It will be
# used by the external components.
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HAF_PRIVATE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
  SOURCES ${sources} HEADERS ${headers})

set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})

target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_ALLOW_ACCELERATION)
target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_SHOW_FPS)

target_compile_definitions(${CURRENT_TARGET} PUBLIC HAF_PROFILE)
target_compile_definitions(${CURRENT_TARGET} PUBLIC HAF_DEBUG_VARIABLES)


# Prepare the haf libray
target_compile_definitions(${CURRENT_TARGET} PRIVATE haf_EXPORTS)
target_link_libraries(${CURRENT_TARGET} PRIVATE
  renderer
  hosted_app
  agloader
  backend
  backend_dev
)

target_link_libraries(${CURRENT_TARGET} PUBLIC log_and_types mc_serial parpar facil_math)
target_link_libraries(${CURRENT_TARGET} PUBLIC haf_imgui)
set_pragma_once_or_not(HAF true PUBLIC)

# For now, we need it public for tests.
# TODO: Fix it
target_include_directories(${CURRENT_TARGET}
                           PUBLIC ${HAF_PRIVATE_INCLUDE_DIRECTORY})

# TODO: Investigate some day if(MSVC) set_target_properties(${CURRENT_TARGET}
# PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB") endif()
addTestingDirectory(tests)
