project(host_haf_interface)
cmake_minimum_required(VERSION 3.14)

set (CURRENT_TARGET ${PROJECT_NAME})

set(headers
    host_haf_interface/include/isystem_controller.hpp
)

build_lib_component(HEADERS_ONLY
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    HEADERS "${headers}"
    )
