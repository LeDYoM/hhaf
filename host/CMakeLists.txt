cmake_minimum_required(VERSION 3.14)
project(
  "Host"
  VERSION 0.5.2.1
  DESCRIPTION "Host component for haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET "host")

set(SRC_FILES 
    src/apploader.cpp
    src/host_config.hpp
    src/host_private.hpp
    src/host.cpp
    src/main.cpp
    src/systemcontroller_loader.cpp
)

build_lib_component(HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SRC_FILES})

configure_file(
  "${PROJECT_SOURCE_DIR}/${CURRENT_TARGET}/include/host_version.hpp.in"
  "${PROJECT_SOURCE_DIR}/${CURRENT_TARGET}/include/host_version.hpp" @ONLY)

  target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE memmanager)
target_link_libraries(${CURRENT_TARGET} PRIVATE hlog)
target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
