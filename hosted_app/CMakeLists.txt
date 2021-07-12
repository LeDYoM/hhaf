project(hosted_app)
cmake_minimum_required(VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})

set(include_dir ${PROJECT_SOURCE_DIR}/hosted_app/include)
set(headers 
    ${include_dir}/iapp.hpp
    )

build_lib_component(HEADERS_ONLY
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    HEADERS "${headers}"
    )
