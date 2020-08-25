project(scene CXX)
cmake_minimum_required(VERSION 3.12)

set(_SOURCES
    i_include/scenecontroller.hpp
    i_include/scenemanager.hpp
    src/componentcontainer_update.cpp
    src/componentcontainer_no_update.cpp
    src/interface_getter.cpp
    src/scenecontroller.cpp
    src/scenemanager.cpp
    src/scenenode.cpp
    src/scenenodefactory.cpp
    src/scenenodes.cpp
    src/scenenodes_group.cpp
    src/matrix4x4.cpp
    src/transformable.cpp
    src/transformation.cpp)

set(CURRENT_TARGET ${PROJECT_NAME})

set(INTERNAL_TARGET scene)
set(_LINK_PRIVATE
    time
    scene_components
    scene_nodes
    backend_dev
    hosted_app
    render
    system_internal)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})
