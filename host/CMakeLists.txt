cmake_minimum_required(VERSION 3.14)
project(
  "Host"
  VERSION 0.5.2.1
  DESCRIPTION "Host component for haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET "host")

set(SRC_FILES "src/apploader.cpp" "src/host.cpp" "src/main.cpp")

build_lib_component(HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SRC_FILES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE HOST_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
target_link_libraries(${CURRENT_TARGET} PRIVATE memmanager)
target_link_libraries(${CURRENT_TARGET} PRIVATE hlog)
target_link_libraries(${CURRENT_TARGET} PRIVATE haf_instancer)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
