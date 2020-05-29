cmake_minimum_required(VERSION 3.14)
project(
  "Host"
  VERSION 0.5.1.1
  DESCRIPTION "Host component for haf"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX)

set(CURRENT_TARGET "host")

set(SRC_FILES "src/apploader.cpp" "src/host.cpp" "src/main.cpp")

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SRC_FILES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE HOST_EXPORTS)

target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
#target_link_libraries(${CURRENT_TARGET} PRIVATE memmanager)
#target_link_libraries(${CURRENT_TARGET} PRIVATE hlog)
target_link_libraries(${CURRENT_TARGET} PRIVATE haf)
target_link_libraries(${CURRENT_TARGET} PRIVATE loader)
