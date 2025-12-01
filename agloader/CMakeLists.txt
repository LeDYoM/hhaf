cmake_minimum_required(VERSION 4.0)
project(
  "AGLoader"
  VERSION 0.2.1.2
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET agloader)

if(MSVC)
  set(driver_file msvc)
else()
  set(driver_file linux)
endif()

set(sources
  src/loaded_instance_utils.cppm
  src/loaded_instance_${driver_file}.cppm
  src/loaded_instance.cppm
  src/loader.cppm
)

build_lib_module(${CURRENT_TARGET} SOURCES ${sources})
set_target_properties(${CURRENT_TARGET} PROPERTIES VISIBILITY_INLINES_HIDDEN TRUE)
target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
