project(memmanager)
cmake_minimum_required(VERSION 3.11)

set(CURRENT_TARGET memmanager)

set(SOURCES "src/memmanager.cpp")

add_library(${CURRENT_TARGET} SHARED ${SOURCES})
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})
