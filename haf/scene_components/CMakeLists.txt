project (scene_components CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/animation.cpp"
    "src/animationcomponent.cpp"
    "src/discretetextcomponent.cpp"
    "src/scenecontrol.cpp"
    "src/scenemetrics.cpp"
    "src/scenemetricsview.cpp"
    "src/texteditorcomponent.cpp"
    "src/visibility_selector.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

build_internal_lib_component(
    HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES
    ${_SOURCES}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_internal)
