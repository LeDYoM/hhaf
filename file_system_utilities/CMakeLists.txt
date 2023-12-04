set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("fsu"
    VERSION 0.0.1.0
    DESCRIPTION "File System Utils"
    LANGUAGES CXX
)

set(CURRENT_TARGET fsu)

set(include_dir fsu/include)
set(headers
    ${include_dir}/file.hpp
)

set(sources
    src/file.cpp
)

build_lib_component(STATIC HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
${sources} HEADERS ${headers})

set_pragma_once_or_not(FSU true PUBLIC)

target_compile_features(${CURRENT_TARGET} PRIVATE cxx_std_20)

addTestingDirectory(tests)
