cmake_minimum_required (VERSION 3.14)
project(haf_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    scene/color
    scene/scenecontroller
    scene/scenenodefactory
    scene/scenenode
    scene/scenenodeparent
    scene/scenemanager

    scene_components/componentcontainer
    scene_components/statescontroller

    shareddata/shareddata
    shareddata/shareddatasystem
    shareddata/shareddataview

    time/timepoint

    utils/object_factory
)

add_haf_test_executable(SOURCE_TESTS ${SOURCE_TESTS})
target_include_directories(${CURRENT_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${CURRENT_TARGET} PRIVATE scene_internal)
target_link_libraries(${CURRENT_TARGET} PRIVATE shareddata_internal)
target_link_libraries(${CURRENT_TARGET} PRIVATE shareddata)
target_link_libraries(${CURRENT_TARGET} PRIVATE system_internal)


