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

set(PUBLIC_HEADERS 
  agloader/include/loader_export.hpp
  agloader/include/loader.hpp
  )

set(PUBLIC_HEADERS_DIRECTORY include)

add_library(${CURRENT_TARGET} SHARED "${SOURCES}")

target_compile_definitions(${CURRENT_TARGET} PRIVATE loader_EXPORTS)

target_include_directories(
  ${CURRENT_TARGET}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
set_output_directories(${CURRENT_TARGET})

set_target_properties(${CURRENT_TARGET}
    PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)
