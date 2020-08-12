project (scene_nodes CXX)
cmake_minimum_required(VERSION 3.14)

set (_SOURCES 
    "src/renderizable_scenenode.cpp"
    "src/scenenodetext.cpp"
    "src/tablenode_imp.cpp"
    "src/textquad.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

set(INTERNAL_TARGET scene_nodes)
set(_LINK_PRIVATE scene)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})
