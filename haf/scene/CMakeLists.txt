set(_SOURCES
    i_include/scenecontroller.hpp
    i_include/scenemanager.hpp
    src/componentcontainer_no_update.cpp
    src/componentcontainer_update.cpp
    src/componentcontainer.cpp
    src/interface_getter.cpp
    src/scenecontroller.cpp
    src/scenemanager.cpp
    src/scenenode_utils.cpp
    src/scenenode.cpp
    src/scenenodefactory.cpp
    src/scenenodes.cpp
    src/matrix4x4.cpp
    src/transformable.cpp
    src/transformation.cpp)

build_internal_lib_component(SOURCES ${_SOURCES})
