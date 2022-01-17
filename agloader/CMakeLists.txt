cmake_minimum_required(VERSION 3.14)
project(
  "AG Loader"
  VERSION 1.1.1.2
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET agloader)

set(SOURCES 
  src/loadedinstance.cpp 
  src/loader.cpp
  )

set(HEADERS 
  agloader/include/loader_export.hpp
  agloader/include/loader.hpp
  )

set(PUBLIC_HEADERS_DIRECTORY include)

build_lib_component(HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    "${SOURCES}" HEADERS "${HEADERS}")

#target_include_directories(
#  ${CURRENT_TARGET}
#  PUBLIC $<INSTALL_INTERFACE:include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
#  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_compile_definitions(${CURRENT_TARGET} PRIVATE loader_EXPORTS)
target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
set_output_directories(${CURRENT_TARGET})
