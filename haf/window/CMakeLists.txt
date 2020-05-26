project (window CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "i_include/window.hpp"
    "src/window.cpp"
    "src/window_properties.cpp"
    )

set (CURRENT_TARGET  ${PROJECT_NAME})

set(INTERNAL_TARGET window)
set(_LINK_PRIVATE backend backend_dev input_internal render_internal)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})
