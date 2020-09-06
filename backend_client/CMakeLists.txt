cmake_minimum_required(VERSION 3.14)
project(
  backend_client
  VERSION 0.8.1.2
  DESCRIPTION "Client library for libraries providing backend functionality"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set (CURRENT_TARGET ${PROJECT_NAME})

set(SOURCES 
    src/default_backend_manager.cpp
    src/default_functions.cpp)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE backend_client_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
