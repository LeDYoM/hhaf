project(filesystem CXX)
cmake_minimum_required(VERSION 3.12)

set(CURRENT_TARGET ${PROJECT_NAME})

set(_SOURCES "i_include/filesystem.hpp" "src/fileserializer.cpp"
             "src/filesystem.cpp")

set(INTERNAL_TARGET filesystem)
set(_LINK_PRIVATE system_internal)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})
