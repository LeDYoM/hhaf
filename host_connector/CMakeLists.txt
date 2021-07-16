project(host_connector)
cmake_minimum_required(VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

set(include_dir ${PROJECT_SOURCE_DIR}/host_connector/include)
set(headers 
    ${include_dir}/ihost_connector.hpp
    )

build_lib_component(HEADERS_ONLY
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    HEADERS "${headers}"
)
