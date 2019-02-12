project (backend_dev)
cmake_minimum_required (VERSION 3.9.2)


set (CURRENT_TARGET backend_dev)
add_library(${CURRENT_TARGET} INTERFACE)

target_include_directories(backend_dev INTERFACE ${PROJECT_SOURCE_DIR})
