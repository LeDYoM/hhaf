set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.14)
project("HafTypes"
    VERSION 0.9.1.2
    DESCRIPTION "Types for HAF librart"
    # [HOMEPAGE_URL <url-string>]
    LANGUAGES CXX
)

include (testing)
include (functions)
#enable_testing()
set_install_dir()

set(CURRENT_TARGET htypes)

set(SOURCES 
    src/algoutils.cpp
    src/array.cpp
    src/basic_property.cpp
    src/connection.cpp
    src/dictionary.cpp
    src/function.cpp
    src/grouping_property.cpp
    src/lockablevector.cpp
    src/menum.cpp
    src/object_utils.cpp
    src/object.cpp
    src/optional.cpp
    src/p_impl_pointer.cpp
    src/parpar.cpp
    src/properties.cpp
    src/propertystate.cpp
    src/rawmemory.cpp
    src/rect.cpp
    src/serializer.cpp
    src/stack.cpp
    src/str.cpp
    src/vector2d.cpp
    src/types.cpp
    src/vector.cpp)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}" SOURCES
                    ${SOURCES})

target_compile_definitions(${CURRENT_TARGET} PRIVATE htypes_EXPORTS)
target_link_libraries(${CURRENT_TARGET} PUBLIC mtypes memmanager)
