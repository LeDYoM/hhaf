project(hosted_app)
cmake_minimum_required(VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

build_lib_interface_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
        hosted_app/include/iapp.hpp
)
