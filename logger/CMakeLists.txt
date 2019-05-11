project (logger)
cmake_minimum_required (VERSION 3.9.2)

set (CURRENT_TARGET logger)

add_library(${CURRENT_TARGET} INTERFACE)
target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})
