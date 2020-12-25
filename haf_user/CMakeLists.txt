cmake_minimum_required(VERSION 3.14)
project(
  "HAF User"
  VERSION 0.0.1.0
  DESCRIPTION "Static library with small utilities to be used by clientes of haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET "haf_user")

set(SRC_FILES 
    src/iapp_with_default_app_versioning_system.cpp
)

build_lib_component(STATIC HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SRC_FILES})

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
