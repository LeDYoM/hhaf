cmake_minimum_required(VERSION 3.14)
project(backend)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCES
    src/backend_creator.cpp
    src/backend_factory.cpp
    src/backend_log.hpp
    src/backend_register.cpp
    src/backend_utils.hpp
)

set(include_dir ${PROJECT_NAME}/include)

set(headers
    ${include_dir}/backend_creator.hpp
    ${include_dir}/backend_factory.hpp
    ${include_dir}/backend_register.hpp
)
build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    "${SOURCES}" HEADERS "${headers}")

target_link_libraries(${CURRENT_TARGET} PRIVATE agloader log_and_types)
target_link_libraries(${CURRENT_TARGET} PUBLIC backend_dev)
