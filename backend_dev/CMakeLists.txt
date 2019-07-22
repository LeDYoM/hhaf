project (backend_dev)
cmake_minimum_required (VERSION 3.11)

set (CURRENT_TARGET ${PROJECT_NAME})
add_library(${CURRENT_TARGET} INTERFACE)

target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})
