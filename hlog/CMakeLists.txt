cmake_minimum_required(VERSION 3.11)
project(hlog LANGUAGES CXX)

set(CURRENT_TARGET hlog)

set(sources
    src/hlog.cpp
    )

set(include_dir hlog/include)
set(headers
    ${include_dir}/hlog.hpp
    )

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

target_link_libraries(${CURRENT_TARGET} PUBLIC logger htypes)
set_compile_warning_level_and_cxx_properties_all(${CURRENT_TARGET})
