# Host Application Framework
cmake_minimum_required(VERSION 3.16)
project(
  hhaf
  VERSION 1.0.1
  DESCRIPTION "Host Application Framework"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)
set(CMAKE_INSTALL_PREFIX hhaf)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include(functions)
setOptions()
includeForOptions()

set(_REPO_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# First for the generic no-config case (e.g. with mingw, Ninja, Makefiles...)
if(DEFINED CMAKE_BUILD_TYPE)
  message("Mono-config generator. Config type: " ${CMAKE_BUILD_TYPE})
  message("Output directory " ${_REPO_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${_REPO_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${_REPO_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${_REPO_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
endif()

# Second, for multi-config builds (e.g. msvc)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  message("For config " ${OUTPUTCONFIG} " we have "
          ${_REPO_OUTPUT_DIRECTORY}/${OUTPUTCONFIG})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG}
      ${_REPO_OUTPUT_DIRECTORY}/${OUTPUTCONFIG})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG}
      ${_REPO_OUTPUT_DIRECTORY}/${OUTPUTCONFIG})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG}
      ${_REPO_OUTPUT_DIRECTORY}/${OUTPUTCONFIG})
endforeach()

# Create interface library to add loggger and types with memory management
# in one line.
add_library(log_and_types INTERFACE)
target_link_libraries(log_and_types INTERFACE htypes memmanager hlog)

add_subdirectory(tools)
add_subdirectory(glad)

set(hhaf_core_module_list
  agloader
  logger
  memmanager
  htypes
  hlog
  host_connector
  hosted_app
  host
  backend_dev
  backend
  hogl
  haf
  haf_user
  haf_run
)

#set(module_list "${hhaf_core_module_list};${backend_module_list}")
set(module_list "${hhaf_core_module_list}")
foreach(target ${module_list})
  message("Adding module: ${target}")
  add_subdirectory(${target})
endforeach()

#add_subdirectory(haf_ext)
add_subdirectory(backend_client)
add_subdirectory(backend_sfml)
add_subdirectory(haf_integrated_backend)
#add_subdirectory(zoper_game)
add_subdirectory(apps/haf_life_game)

#add_subdirectory(external/opengl_testing)
#add_subdirectory(haf_app_menu)
#add_subdirectory(haf_app_middleware)

#if(BUILD_PACKAGES)
#  generate_package("${hhaf_core_module_list}")
#endif()

build_docs("${module_list}")
