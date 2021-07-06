cmake_minimum_required(VERSION 3.14)
project(
  "Host"
  VERSION 0.5.4.1
  DESCRIPTION "Host component for haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET host)

set(sources 
  src/app_loader.cpp
  src/app_loader.hpp
  src/app_state.hpp
  src/host_config.hpp
  src/host_private.cpp
  src/host_private.hpp
  src/host.cpp
  src/hosted_app_group.cpp
  src/hosted_app_group.hpp
  src/hosted_application.cpp
  src/hosted_application.hpp
  src/main.cpp
  src/managed_app.hpp
  src/systemcontroller_loader.cpp
  src/systemcontroller_loader.hpp
)

set(include_dir host/include)

set(headers 
  ${include_dir}/host.hpp
)

build_lib_component(HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

configure_file(
  "${PROJECT_SOURCE_DIR}/config/host_version.hpp.in"
  "${PROJECT_BINARY_DIR}/host_version.hpp" @ONLY)
target_include_directories(${CURRENT_TARGET} PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app memmanager hlog agloader haf)
#export(TARGETS ${CURRENT_TARGET} FILE HostTarget.cmake EXPORT_LINK_INTERFACE_LIBRARIES)
