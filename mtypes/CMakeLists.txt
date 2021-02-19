set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("Minitypes"
    VERSION 0.9.1.2
    DESCRIPTION "Simple types for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

include (testing)
include (functions)
enable_testing()
set_install_dir()

set(CURRENT_TARGET mtypes)

add_library(${CURRENT_TARGET} INTERFACE)

#target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})

target_include_directories(${CURRENT_TARGET}
    INTERFACE 
        $<INSTALL_INTERFACE:.>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

file(GLOB_RECURSE public_headers *.hpp)
set_target_properties(${CURRENT_TARGET} PROPERTIES PUBLIC_HEADER "${public_headers}")

install(
  TARGETS ${CURRENT_TARGET}
  PUBLIC_HEADER DESTINATION ${CURRENT_TARGET}/include
  )

add_subdirectory(tests)

build_doc(${CURRENT_TARGET})
