cmake_minimum_required (VERSION 3.14)
project(haf_utests CXX)

set(CURRENT_TARGET ${PROJECT_NAME})

set(SOURCE_TESTS
    animation/animation_component

    components/component_container

    debug_system/debug_variable
    debug_system/debug_variables

    events/connection

    file_system/file_system

    input/keyboard_input_component

    properties/properties
    properties/propertystate

    render/mesh_render_component
    render/vertex_formats

    resources/image

    scene/scenenode
    scene/scenenodefactory
    scene/scenenodeparent
    scene/scenenodes
    scene/transformable
    scene/transformation

    scene_components/global_transformation_component
    scene_components/scene_nodes_component
    scene_components/states_controller_component
    scene_components/transformation_component
    scene_components/visibility_selector_component

    shareddata/address
    shareddata/shared_data_system
    shareddata/shared_data_updater
    shareddata/shared_data_viewer
    shareddata/shared_data

    time/timepoint
    time/timesystem

    utils/object_factory
)

add_haf_test_executable(SOURCE_TESTS ${SOURCE_TESTS})
target_include_directories(${CURRENT_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})

