project (scene CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/componentcontainer.cpp"
    "src/renderizable.cpp"
    "src/renderizables.cpp"
    "src/scenecontroller.cpp"
    "src/scenemanager.cpp"
    "src/scenenode.cpp"
    "src/scenenodefactory.cpp"
    "src/scenenodes.cpp"
    "src/transform.cpp"
    "src/transformable.cpp"
    "src/vertexarray.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)
target_link_libraries(${CURRENT_TARGET} PRIVATE time)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_components)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_nodes)
target_link_libraries(${CURRENT_TARGET} PRIVATE backend_dev)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app)
