cmake_minimum_required(VERSION 3.2)

project (parpar)

set (CURRENT_TARGET parpar)
set(CMAKE_CXX_STANDARD 14)

add_library(${CURRENT_TARGET} INTERFACE)
target_include_directories(${CURRENT_TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_sources(${CURRENT_TARGET} INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/parpar/include/parpar.hpp
)

add_subdirectory(tests)
