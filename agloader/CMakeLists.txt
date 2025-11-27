cmake_minimum_required(VERSION 3.14)
project(
  "AG Loader"
  VERSION 1.1.1.2
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET agloader)
build_lib_module(${CURRENT_TARGET})

#add_library(${CURRENT_TARGET} SHARED)
set_target_properties(${CURRENT_TARGET} PROPERTIES VISIBILITY_INLINES_HIDDEN TRUE)

if(MSVC)
  set(driver_file loadedinstance_windows.cppm)
else()
  set(driver_file loadedinstance_linux.cppm)
endif()

target_sources(${CURRENT_TARGET}
PUBLIC
  FILE_SET CXX_MODULES
  FILES
  src/${driver_file}
  src/loaded_instance.cppm
  src/loader.cppm
)

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
