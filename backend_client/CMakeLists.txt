cmake_minimum_required(VERSION 3.14)
project(
  backend_client
  VERSION 1.0.1.2
  DESCRIPTION "Client library for libraries providing backend functionality"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set (CURRENT_TARGET ${PROJECT_NAME})

set(include_dir backend_client/include)
set(headers 
  ${include_dir}/autoregisterfactory.hpp
  ${include_dir}/backend_client_exports.hpp
  ${include_dir}/default_backend_manager.hpp
  ${include_dir}/default_factory.hpp
  ${include_dir}/ibackendmanager.hpp
  )

set(sources 
    src/default_backend_manager.cpp
    src/default_functions.cpp
    )

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

target_compile_definitions(${CURRENT_TARGET} PRIVATE backend_client_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev htypes)
