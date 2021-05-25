set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("Minitypes"
    VERSION 0.9.2.0
    DESCRIPTION "Simple types for HAF"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

include (testing)
include (functions)
enable_testing()

set(CURRENT_TARGET htypes)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE htypes_EXPORTS)

# Use Memmamanger
target_compile_definitions(${CURRENT_TARGET} PUBLIC USER_MEM_MANAGER)
target_link_libraries(${CURRENT_TARGET} PUBLIC memmanager)

add_subdirectory(tests)
