project (scene_nodes CXX)
cmake_minimum_required(VERSION 3.14)

set (_SOURCES 
    "src/renderizable_scenenode.cpp"
    "src/scenenodetext.cpp"
    "src/textquad.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
