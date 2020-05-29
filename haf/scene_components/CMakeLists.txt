project (scene_components CXX)
cmake_minimum_required(VERSION 3.12)

set (_SOURCES 
    "src/animation.cpp"
    "src/animationcomponent.cpp"
    "src/discretetextcomponent.cpp"
    "src/scenecontrol.cpp"
    "src/scenefactory.cpp"
    "src/scenemetrics.cpp"
    "src/scenemetricsview.cpp"
    "src/texteditorcomponent.cpp"
    "src/visibility_selector.cpp"
)

set (CURRENT_TARGET  ${PROJECT_NAME})

set(INTERNAL_TARGET scene_components)
set(_LINK_PRIVATE scene scene_internal)

build_internal_lib_component(INTERNAL_TARGET ${INTERNAL_TARGET} SOURCES
                             ${_SOURCES} PRIVATE_INTERNAL_LINK ${_LINK_PRIVATE})

target_link_libraries(${CURRENT_TARGET} PRIVATE scene)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_internal)
