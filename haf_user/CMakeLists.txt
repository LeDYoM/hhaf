cmake_minimum_required(VERSION 3.14)
project(
  "HAF User"
  VERSION 0.0.1.0
  DESCRIPTION "Static library with small utilities to be used by clientes of haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET haf_user)

set(sources 
    src/iapp_with_default_app_versioning_system.cpp
)

set(include_dir haf_user/include)
set(headers
  ${include_dir}/declare_app.hpp
  ${include_dir}/export_app.hpp
  ${include_dir}/iapp_with_default_app_versioning_system.hpp
  ${include_dir}/iapp_with_host_access.hpp
  )

build_lib_component(STATIC HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app htypes)
