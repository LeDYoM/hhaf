project(resources_interface)
cmake_minimum_required(VERSION 3.12)

set (CURRENT_TARGET ${PROJECT_NAME})

build_lib_interface_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
