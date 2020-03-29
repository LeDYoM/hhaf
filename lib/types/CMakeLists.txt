cmake_minimum_required (VERSION 3.11)
project (types CXX)

set (CURRENT_TARGET ${PROJECT_NAME})
add_library(${CURRENT_TARGET} INTERFACE)

target_include_directories(${CURRENT_TARGET} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${CURRENT_TARGET} INTERFACE mtypes)
