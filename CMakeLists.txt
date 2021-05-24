# Host Application Framework
cmake_minimum_required(VERSION 3.14)
project(
  hhaf
  VERSION 0.2.1
  DESCRIPTION "Host Application Framework"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

option(BUILD_TESTS "Build test programs" ON)
option(BUILD_PACKAGES "Build packages" OFF)
option(BUILD_TOOLS "Build tools" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

if (BUILD_TESTS)
message("Building tests")
  enable_testing()
  include(testing)
  add_subdirectory(tests)
else()
  message("Not building tests")
endif()

include(functions)
if(BUILD_PACKAGES)
  include(install)
  message("Building packages")
else()
  message("Not building packages")
endif()

if(BUILD_TOOLS)
  add_subdirectory(tools)
endif()

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
add_subdirectory(haf_user)
add_subdirectory(haf_run)

add_subdirectory(haf_ext)

add_subdirectory(backend_sfml)
add_subdirectory(zoper_game)
add_subdirectory(haf_app_menu)

stardard_install_haf()
