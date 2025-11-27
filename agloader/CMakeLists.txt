cmake_minimum_required(VERSION 3.14)
project(
  "AGLoader"
  VERSION 0.2.1.2
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET agloader)
build_lib_module(${CURRENT_TARGET})

set_target_properties(${CURRENT_TARGET} PROPERTIES VISIBILITY_INLINES_HIDDEN TRUE)

if(MSVC)
  set(driver_file msvc)
else()
  set(driver_file linux)
endif()

target_sources(${CURRENT_TARGET}
PUBLIC
  FILE_SET CXX_MODULES
  FILES
  src/loaded_instance_utils.cppm
  src/loaded_instance_${driver_file}.cppm
  src/loaded_instance.cppm
  src/loader.cppm
)

target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
