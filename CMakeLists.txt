# Host Application Framework
cmake_minimum_required(VERSION 3.16)
project(
  hhaf
  VERSION 0.2.1
  DESCRIPTION "Host Application Framework"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include(functions)
setOptions()
includeForOptions()

add_subdirectory(tools)

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

if(BUILD_PACKAGES)
  stardard_install_haf()
endif()
