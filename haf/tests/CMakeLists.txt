cmake_minimum_required (VERSION 3.14)
project(haf_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    scene/color
    scene/matrix4x4
    scene/scenecontroller
    scene/scenemanager
    scene/scenenode
    scene/scenenodefactory
    scene/scenenodeparent
    scene/scenenodes
    scene/transformable
    scene/transformation

    scene_components/animationcomponent
    scene_components/componentcontainer
    scene_components/statescontroller

    shareddata/address
    shareddata/shareddata
    shareddata/shareddatasystem
    shareddata/shareddataupdater
    shareddata/shareddataviewer

    time/timepoint
    time/timesystem

    utils/object_factory
)

add_haf_test_executable(SOURCE_TESTS ${SOURCE_TESTS})
target_include_directories(${CURRENT_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})