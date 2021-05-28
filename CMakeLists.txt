# Host Application Framework
cmake_minimum_required(VERSION 3.16)
project(
  hhaf
  VERSION 1.0.1
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

#add_subdirectory(agloader)
#add_subdirectory(logger)
#add_subdirectory(memmanager)
#add_subdirectory(htypes)
#add_subdirectory(hlog)

# Create interface library to add loggger and types with memory management
# in one line.
#add_library(log_and_types INTERFACE)
#target_link_libraries(log_and_types INTERFACE htypes memmanager hlog)

#add_subdirectory(tools)

set(hhaf_core_module_list
  agloader
#  hosted_app
#  host
#  haf
#  haf_user
#  haf_run
)

set(backend_module_list 
  backend
  backend_dev
  backend_client
  )

#set(module_list "${hhaf_core_module_list};${backend_module_list}")
set(module_list "${hhaf_core_module_list}")
foreach(target ${module_list})
  message("Adding module: ${target}")
  add_subdirectory(${target})
endforeach()

#add_subdirectory(haf_ext)

#add_subdirectory(backend_sfml)
#add_subdirectory(zoper_game)
#add_subdirectory(haf_app_menu)

#if(BUILD_PACKAGES)
  generate_package("${hhaf_core_module_list}")
#endif()

#build_docs("${module_list}")
