project(htypes)
cmake_minimum_required(VERSION 3.11)

set(CURRENT_TARGET htypes)

set(SOURCES "src/htypes.cpp")

build_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PUBLIC mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE memmanager)
