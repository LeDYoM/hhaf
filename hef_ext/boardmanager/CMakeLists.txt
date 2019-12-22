project(boardmanager)
cmake_minimum_required(VERSION 3.12)

set (CURRENT_TARGET ${PROJECT_NAME})

set(SRC_FILES "src/boardmodel.cpp")

build_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${SRC_FILES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE lib)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
