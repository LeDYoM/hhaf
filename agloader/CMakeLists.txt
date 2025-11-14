cmake_minimum_required(VERSION 3.14)
project(
  "AG Loader"
  VERSION 1.1.1.2
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

# These will be discussed later in the article
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

set(CURRENT_TARGET agloader)
add_library(${CURRENT_TARGET} SHARED)

target_sources(${CURRENT_TARGET}
    PRIVATE
      src/loadedinstance_private.hpp
      src/loadedinstance.cpp
      src/loadedinstance.hpp
    PUBLIC
      FILE_SET CXX_MODULES
      FILES
        src/loader.cppm
        src/loader.cpp
        )

#set(PUBLIC_HEADERS_DIRECTORY include)

# build_lib_component(HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
#                    "${SOURCES}" HEADERS "${HEADERS}")

set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})

#target_include_directories(
#  ${CURRENT_TARGET}
#  PUBLIC $<INSTALL_INTERFACE:include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
#  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_compile_definitions(${CURRENT_TARGET} PRIVATE loader_EXPORTS)
target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
set_output_directories(${CURRENT_TARGET})
