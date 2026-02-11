cmake_minimum_required(VERSION 3.14)
project(
  "Host"
  VERSION 0.5.5.1
  DESCRIPTION "Host component for haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET host)

set(sources
  src/app_loader.cppm
  src/app_state.cppm
  src/host_config.cppm
  src/host_connector_impl.cppm
  src/host_connector.cppm
#  src/host_export.hpp
  src/host_internal.cppm
  src/host_log.cppm
  src/host_module.cppm
  src/host.cppm
  src/hosted_app_group.cppm
  src/hosted_application.cppm
  src/main.cppm
  src/managed_app.cppm
  src/system_controller_loader.cppm
)

build_lib_component(HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources})

target_link_libraries(${CURRENT_TARGET} PRIVATE
  host_connector
  hosted_app
  memmanager
  parpar
  hlog
  agloader
  host_haf_interface
  backend
  facil_math
)

#export(TARGETS ${CURRENT_TARGET} FILE HostTarget.cmake EXPORT_LINK_INTERFACE_LIBRARIES)
