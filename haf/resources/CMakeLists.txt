project(resources CXX)
cmake_minimum_required(VERSION 3.12)

set(_SOURCES
    i_include/bmpfont.hpp
    i_include/bmpfont_private.hpp
    i_include/bmpfontfactory.hpp
    i_include/resourcemanager.hpp
    i_include/resources_config_data.hpp
    i_include/shader.hpp
    i_include/texture.hpp
    i_include/ttfont.hpp
    i_include/ttfontinstance.hpp
    src/bmpfont.cpp
    src/bmpfontfactory.cpp
    src/iresourceconfigurator.cpp
    src/resourcemanager.cpp
    src/resourceview.cpp
    src/shader.cpp
    src/texture.cpp
    src/ttfont.cpp
    src/ttfontinstance.cpp)

set(CURRENT_TARGET ${PROJECT_NAME})

set(INTERNAL_TARGET resources)
set(_LINK_PRIVATE backend backend_dev system_internal)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})
