project (simulation CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/simulationsystem.cpp"
    "src/simulationsystem_private.hpp"
    )


set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE time)
