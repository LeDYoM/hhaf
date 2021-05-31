cmake_minimum_required(VERSION 3.11)
project(hlog LANGUAGES CXX)

set(CURRENT_TARGET hlog)

set(sources 
    src/cout_commiter.cpp
    src/file_commiter.cpp
    src/thread_commiter.cpp
    src/hlog.cpp
    )

set(include_dir hlog/include)
set(headers
    ${include_dir}/cout_commiter.hpp
    ${include_dir}/file_commiter.hpp
    ${include_dir}/hlog.hpp
    ${include_dir}/thread_commiter.hpp
    )

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${sources} HEADERS ${headers})

find_package(Threads REQUIRED)
target_link_libraries(${CURRENT_TARGET} PRIVATE Threads::Threads)

target_link_libraries(${CURRENT_TARGET} PUBLIC logger)
target_link_libraries(${CURRENT_TARGET} PUBLIC htypes)
