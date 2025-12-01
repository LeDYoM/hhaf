set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("PARameter PARser"
    VERSION 1.0.0.1
    DESCRIPTION "Parameter Parser"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES C CXX
)

set(CURRENT_TARGET parpar)

set(sources
    src/parpar_mini.cppm
    src/parpar.cppm
)

build_lib_module(${CURRENT_TARGET} STATIC SOURCES "${sources}")

target_link_libraries(${CURRENT_TARGET} PRIVATE htypes)
addTestingDirectory(tests)
