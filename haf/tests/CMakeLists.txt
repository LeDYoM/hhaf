cmake_minimum_required (VERSION 3.14)
project(lib_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    main

    scene/color
    scene/scenecontroller
    scene/scenenodefactory
    scene/scenenode
    scene/scenenodeparent
    scene/scenemanager

    scene_components/componentcontainer
    scene_components/statescontroller

    utils/object_factory
)

add_test_executable(SOURCE_TESTS ${SOURCE_TESTS})

target_link_libraries(${CURRENT_TARGET} PRIVATE lib)
target_link_libraries(${CURRENT_TARGET} PRIVATE mtypes)
target_link_libraries(${CURRENT_TARGET} PRIVATE logger)

#catch_discover_tests(${CURRENT_TARGET})
