# Host Application Framework
cmake_minimum_required(VERSION 3.14)
project(
  haf_repo
  VERSION 0.2.1
  DESCRIPTION "Host Application Framework"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags and options. Here it is setting the Visual Studio warning
# level to 4
if(MSVC)
  add_compile_definitions(/W4 /WX)
else()
  add_compile_definitions(-Wall -Wextra -pedantic -Werror)
endif()

add_compile_definitions(HAF_ALLOW_ACCELERATION)

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

# Use the memmanager
option(MTYPES_USE_MEMMANAGER "Compile mtypes using the memmanager wrappers" ON)

# Prepare the test framework
add_subdirectory(tests)

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(memmanager)
add_subdirectory(mtypes)
add_subdirectory(logger)

# Create interface library to add loggger and types with memory management
# in one line.
add_library(log_and_types INTERFACE)
target_link_libraries(log_and_types INTERFACE mtypes memmanager hlog)

add_subdirectory(hlog)
add_subdirectory(loader)
add_subdirectory(hosted_app)
add_subdirectory(host)
add_subdirectory(backend_dev)
add_subdirectory(backend)
add_subdirectory(haf)
add_subdirectory(haf_ext)
add_subdirectory(backend_sfml)
add_subdirectory(zoper_game)
add_subdirectory(haf_run)
