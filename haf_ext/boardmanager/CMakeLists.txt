project(boardmanager)
cmake_minimum_required(VERSION 3.12)

set (CURRENT_TARGET ${PROJECT_NAME})

set(SRC_FILES "src/boardmanager.cpp")

build_lib_ext(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SRC_FILES}
)

add_subdirectory(tests)
