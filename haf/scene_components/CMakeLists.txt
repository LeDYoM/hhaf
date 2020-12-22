set (_SOURCES 
    src/animation.cpp
    src/animationcomponent.cpp
    src/discretetextcomponent.cpp
    src/scene_group_initializer.cpp
    src/scenecontrol.cpp
    src/scenefactory.cpp
    src/scenemetrics.cpp
    src/scenemetricsview.cpp
    src/texteditorcomponent.cpp
    src/visibility_selector.cpp
)

build_internal_lib_component(SOURCES ${_SOURCES})
