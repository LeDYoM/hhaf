cmake_minimum_required (VERSION 3.14)
project(haf_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    animation/animation_component

    components/component_container

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

    scene_components/states_controller_component

    shareddata/address
    shareddata/shareddata
    shareddata/shareddatasystem
    shareddata/shareddataupdater
    shareddata/shareddataviewer

    time/timepoint
    time/timesystem

    utils/object_factory
)

set(BENCHMARK_SOURCES
    scene/matrix4x4.benchmark
)

set(no_benchmark 1)

add_haf_test_executable(SOURCE_TESTS ${SOURCE_TESTS})
target_include_directories(${CURRENT_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})

if (NOT DEFINED no_benchmark)
    set(CURRENT_TARGET "${CURRENT_TARGET}_benchmark")
    add_haf_test_executable(SOURCE_TESTS ${BENCHMARK_SOURCES})
    target_include_directories(${CURRENT_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})
endif()
