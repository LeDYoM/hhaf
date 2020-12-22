set (_SOURCES 
    src/animation.cpp
    src/animationcomponent.cpp
    src/app_initializer.cpp
    src/discretetextcomponent.cpp
    src/scenecontrol.cpp
    src/scenefactory.cpp
    src/scenemetrics.cpp
    src/scenemetricsview.cpp
    src/texteditorcomponent.cpp
    src/visibility_selector.cpp
)

build_internal_lib_component(SOURCES ${_SOURCES})
