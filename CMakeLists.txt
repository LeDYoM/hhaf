SET(CMAKE_INSTALL_PREFIX /home/ismael/h_test)

# Host Application Framework
cmake_minimum_required(VERSION 3.14)
project(
  haf_repo
  VERSION 0.2.1
  DESCRIPTION "Host Application Framework"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

# Set compiler flags and options.

#Equivalent to:
if(MSVC)
#  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
  add_compile_options(
      /W4
#      /WX
      )
else()
#  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
  add_compile_options(
#    -Wall
#    -Wextra
#    -pedantic
#    -Werror
  )
endif()

message("CXX Flags: " ${CMAKE_CXX_FLAGS})

set(_REPO_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include(functions)
include(testing)
include(install)

#set(BUILD_PACKAGE_FOR "mtypes")

# Prepare the test framework
add_subdirectory(tests)

add_subdirectory(tools)

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(mtypes)

add_subdirectory(agloader)
add_subdirectory(logger)
add_subdirectory(memmanager)
add_subdirectory(htypes)
add_subdirectory(hlog)

  # Create interface library to add loggger and types with memory management
  # in one line.
add_library(log_and_types INTERFACE)
target_link_libraries(log_and_types INTERFACE htypes memmanager hlog)

add_subdirectory(hosted_app)
add_subdirectory(host)
add_subdirectory(backend_dev)
add_subdirectory(backend_client)
add_subdirectory(backend)
add_subdirectory(haf)
add_subdirectory(haf_ext)
add_subdirectory(haf_user)
add_subdirectory(haf_run)

add_subdirectory(backend_sfml)
add_subdirectory(zoper_game)
add_subdirectory(haf_app_menu)

stardard_install_haf()
