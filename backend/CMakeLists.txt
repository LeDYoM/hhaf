cmake_minimum_required(VERSION 3.14)
project(backend)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCES 
    src/backend_creator.cpp 
    src/backendfactory.cpp
    src/backendregister.cpp
)

set(include_dir ${PROJECT_NAME}/include)

set(headers
    ${include_dir}/backend_creator.hpp
    ${include_dir}/backendfactory.hpp
    ${include_dir}/backendregister.hpp
)
build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    "${SOURCES}" HEADERS "${headers}")

target_link_libraries(${CURRENT_TARGET} PRIVATE agloader htypes backend_dev)

