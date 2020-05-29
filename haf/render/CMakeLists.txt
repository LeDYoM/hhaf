project(render CXX)
cmake_minimum_required(VERSION 3.12)

set(_SOURCES "i_include/rendersystem.hpp" "i_include/rendertarget.hpp"
             "src/rendersystem.cpp" "src/rendertarget.cpp")

set(CURRENT_TARGET ${PROJECT_NAME})
set(INTERNAL_TARGET render)
set(_LINK_PRIVATE resources resources_internal backend_dev)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})
