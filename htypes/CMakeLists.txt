cmake_minimum_required(VERSION 3.11)
project(htypes LANGUAGES CXX)

set(CURRENT_TARGET htypes)

set(SOURCES 
    src/htypes.cpp)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_link_libraries(${CURRENT_TARGET} PUBLIC mtypes)
