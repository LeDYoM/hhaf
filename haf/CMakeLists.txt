cmake_minimum_required(VERSION 3.14)
project(
  "HAF Main Library"
  VERSION 0.8.2.0
  DESCRIPTION "Host Application Framework main library"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX
)

set(CURRENT_TARGET haf)

set(src_dir src)

set(sources
  # Global
  ${src_dir}/haf_private.hpp
  ${src_dir}/main.cpp
  ${src_dir}/systemprovider_init.cpp

  # Animation
  ${src_dir}/animation/animation.cpp
  ${src_dir}/animation/animation_component.cpp

  # Component
  ${src_dir}/component/component_container.cpp

  # Debug
  ${src_dir}/debug_utils/console.cpp
  ${src_dir}/debug_utils/debug_actions.cpp
  ${src_dir}/debug_utils/debug_system_subsystems_view.cpp
  ${src_dir}/debug_utils/debug_system.cpp
  ${src_dir}/debug_utils/debug_system.hpp
  ${src_dir}/debug_utils/displayvar_console.cpp
  ${src_dir}/debug_utils/memory_data_initializer.cpp
  ${src_dir}/debug_utils/variable_viewer.cpp
  
  # FileSystem
  ${src_dir}/filesystem/file_system_private_funcs.cpp
  ${src_dir}/filesystem/file_system_private_funcs.hpp
  ${src_dir}/filesystem/file_system_subsystems_view.cpp
  ${src_dir}/filesystem/file_system.cpp
  ${src_dir}/filesystem/file_system.hpp

  # Input
  ${src_dir}/input/input_component_base.cpp
  ${src_dir}/input/input_component.cpp
  ${src_dir}/input/input_driver_wrapper.cpp
  ${src_dir}/input/input_system.cpp
  ${src_dir}/input/input_system.hpp
  ${src_dir}/input/stated_input_component_base.cpp
  ${src_dir}/input/virtual_input_component.cpp

  # Random
  ${src_dir}/random/randomnumberscomponent.cpp
  ${src_dir}/random/randomsystem.cpp
  ${src_dir}/random/randomsystem.hpp

  # Render
  ${src_dir}/render/geometry_math.hpp
  ${src_dir}/render/render_data_conversion.cpp
  ${src_dir}/render/render_data_conversion.hpp
  ${src_dir}/render/render_system.cpp
  ${src_dir}/render/render_system.hpp
  ${src_dir}/render/render_target.cpp
  ${src_dir}/render/render_target.hpp
  ${src_dir}/render/renderizable_builder.cpp
  ${src_dir}/render/renderizable_internal_data.hpp
  ${src_dir}/render/renderizable_internal_functions.cpp
  ${src_dir}/render/renderizable_internal_functions.hpp
  ${src_dir}/render/renderizable_private.hpp
  ${src_dir}/render/renderizable.cpp
  ${src_dir}/render/renderizables.cpp
  ${src_dir}/render/vertex_array.cpp

  # Resources
  ${src_dir}/resources/bmpfont_private.cpp
  ${src_dir}/resources/bmpfont_private.hpp
  ${src_dir}/resources/bmpfont.cpp
  ${src_dir}/resources/bmpfont.hpp
  ${src_dir}/resources/bmpfontfactory.cpp
  ${src_dir}/resources/bmpfontfactory.hpp
  ${src_dir}/resources/character_render_data.hpp
  ${src_dir}/resources/font_utils.cpp
  ${src_dir}/resources/font_utils.hpp
  ${src_dir}/resources/resource_manager_config_loader.cpp
  ${src_dir}/resources/resource_manager_config_loader.hpp
  ${src_dir}/resources/resource_manager_subsystems_view.cpp
  ${src_dir}/resources/resource_manager.cpp
  ${src_dir}/resources/resource_manager.hpp
  ${src_dir}/resources/resourcemanager_private.hpp
  ${src_dir}/resources/resources_config_data_element.cpp
  ${src_dir}/resources/resources_config_data_element.hpp
  ${src_dir}/resources/resources_config_data.cpp
  ${src_dir}/resources/resources_config_data.hpp
  ${src_dir}/resources/shader.cpp
  ${src_dir}/resources/shader.hpp
  ${src_dir}/resources/text_render_data.hpp
  ${src_dir}/resources/texture.cpp
  ${src_dir}/resources/texture.hpp
  ${src_dir}/resources/ttfont.cpp
  ${src_dir}/resources/ttfont.hpp
  ${src_dir}/resources/ttfontinstance.cpp
  ${src_dir}/resources/ttfontinstance.hpp

  # Scene
  ${src_dir}/scene/color.cpp
  ${src_dir}/scene/matrix4x4.cpp
  ${src_dir}/scene/scene_controller.cpp
  ${src_dir}/scene/scene_controller.hpp
  ${src_dir}/scene/scene_manager_subsystems_view.cpp
  ${src_dir}/scene/scene_private.cpp
  ${src_dir}/scene/scene_private.hpp
  ${src_dir}/scene/scene_render.cpp
  ${src_dir}/scene/scene_render.hpp
  ${src_dir}/scene/scene.cpp
  ${src_dir}/scene/scene_manager.cpp
  ${src_dir}/scene/scene_manager.hpp
  ${src_dir}/scene/scene_node.cpp
  ${src_dir}/scene/scene_nodes.cpp
  ${src_dir}/scene/scenenodefactory.cpp
  ${src_dir}/scene/transformation.cpp

  # Scene components
  ${src_dir}/scene_components/camera_component.cpp
  ${src_dir}/scene_components/discretetextcomponent.cpp
  ${src_dir}/scene_components/texteditorcomponent.cpp
  ${src_dir}/scene_components/visibility_selector_component.cpp

  # Scene nodes
  ${src_dir}/scene_nodes/renderizable_scene_node.cpp
  ${src_dir}/scene_nodes/renderizables_scene_node.cpp
  ${src_dir}/scene_nodes/scene_node_letter.cpp
  ${src_dir}/scene_nodes/scene_node_letter.hpp
  ${src_dir}/scene_nodes/scene_node_table_imp.cpp
  ${src_dir}/scene_nodes/scene_node_table_text.cpp
  ${src_dir}/scene_nodes/scene_node_text_quad.cpp
  ${src_dir}/scene_nodes/scene_node_text.cpp
  ${src_dir}/scene_nodes/text_base_size.cpp
  ${src_dir}/scene_nodes/transformable_scene_node.cpp

  # Shared data
  ${src_dir}/shareddata/address.cpp
  ${src_dir}/shareddata/shared_data_subsystems_view.cpp
  ${src_dir}/shareddata/shared_data_system.cpp
  ${src_dir}/shareddata/shared_data_system.hpp

  # Simulation
  ${src_dir}/simulation/simulation_system_configuration.hpp
  ${src_dir}/simulation/simulation_system_private.hpp
  ${src_dir}/simulation/simulation_system.cpp
  ${src_dir}/simulation/simulation_system.hpp

  # System
  ${src_dir}/system/get_system_provider.cpp
  ${src_dir}/system/get_system_provider.hpp
  ${src_dir}/system/get_system.cpp
  ${src_dir}/system/get_system.hpp
  ${src_dir}/system/init_system_options.hpp
  ${src_dir}/system/subsystem_interface_definitions.hpp
  ${src_dir}/system/system_access.cpp
  ${src_dir}/system/system_base.cpp
  ${src_dir}/system/system_base.hpp
  ${src_dir}/system/system_controller.cpp
  ${src_dir}/system/system_controller.hpp
  ${src_dir}/system/system_options_init.hpp
  ${src_dir}/system/system_provider_configuration.hpp
  ${src_dir}/system/system_provider.cpp
  ${src_dir}/system/system_provider.hpp
  ${src_dir}/system/system_configuration.hpp

  # Time
  ${src_dir}/time/time_point.cpp
  ${src_dir}/time/time_system_acceleration.cpp
  ${src_dir}/time/time_system_acceleration.hpp
  ${src_dir}/time/time_system_subsystems_view.cpp
  ${src_dir}/time/time_system.cpp
  ${src_dir}/time/time_system.hpp 
  ${src_dir}/time/timer.cpp
  ${src_dir}/time/timer_component.cpp
  ${src_dir}/time/timer_connector.cpp

  # Types
  ${src_dir}/types/str.cpp

  # Utils
  ${src_dir}/utils/compile_time_constants.hpp
  ${src_dir}/utils/type_data.cpp
  
  # Window
  ${src_dir}/window/fps_counter.cpp
  ${src_dir}/window/fps_counter.hpp
  ${src_dir}/window/window_configuration.hpp
  ${src_dir}/window/window_private.cpp
  ${src_dir}/window/window_private.hpp
  ${src_dir}/window/window.cpp
  ${src_dir}/window/window.hpp
  )

set(inc_dir include/haf/include)

set(headers
  # Global
  ${inc_dir}/haf_export.hpp

  # Animation
  ${inc_dir}/animation/animabletypes.hpp
  ${inc_dir}/animation/animation_data.hpp
  ${inc_dir}/animation/animation.hpp
  ${inc_dir}/animation/animation_component.hpp
  ${inc_dir}/animation/property_animation_builder.hpp
  ${inc_dir}/animation/property_animation_data.hpp
  ${inc_dir}/animation/property_animation.hpp

  # Component
  ${inc_dir}/component/component_container.hpp
  ${inc_dir}/component/component.hpp
  ${inc_dir}/component/icomponent_attached_node.hpp
  ${inc_dir}/component/icomponent_mixin.hpp
  ${inc_dir}/component/icomponent.hpp

  # Debug
  ${inc_dir}/debug_utils/console.hpp
  ${inc_dir}/debug_utils/debug_actions.hpp
  ${inc_dir}/debug_utils/displayvar_console.hpp
  ${inc_dir}/debug_utils/imemory_data_viewer.hpp
  ${inc_dir}/debug_utils/memory_data_initializer.hpp
  ${inc_dir}/debug_utils/variable_viewer.hpp

  # Data
  ${inc_dir}/data/ideserializable.hpp
  ${inc_dir}/data/ifullserializable.hpp
  ${inc_dir}/data/iserializable.hpp
  
  # File system
  ${inc_dir}/filesystem/ifile_serializer.hpp
  ${inc_dir}/filesystem/path.hpp

  # Input
  ${inc_dir}/input/input_component_base.hpp
  ${inc_dir}/input/input_component.hpp
  ${inc_dir}/input/inputdriver_wrapper.hpp
  ${inc_dir}/input/key.hpp
  ${inc_dir}/input/stated_input_component_base.hpp
  ${inc_dir}/input/stated_input_component.hpp
  ${inc_dir}/input/virtual_input_component.hpp

  # Random
  ${inc_dir}/random/randomnumberscomponent.hpp

  # Render
  ${inc_dir}/render/fig_type.hpp
  ${inc_dir}/render/primitive_type.hpp
  ${inc_dir}/render/renderizable_builder_data.hpp
  ${inc_dir}/render/renderizable_builder.hpp
  ${inc_dir}/render/renderizable_data.hpp
  ${inc_dir}/render/renderizable_modifier_context.hpp
  ${inc_dir}/render/renderizable.hpp
  ${inc_dir}/render/renderizables.hpp
  ${inc_dir}/render/vertex.hpp
  ${inc_dir}/render/vertex_array.hpp

  # Resources
  ${inc_dir}/resources/ifont.hpp
  ${inc_dir}/resources/iresource_configurator.hpp
  ${inc_dir}/resources/iresource_retriever.hpp
  ${inc_dir}/resources/ishader.hpp
  ${inc_dir}/resources/itexture.hpp
  ${inc_dir}/resources/ittfont.hpp

  # Scene
  ${inc_dir}/scene/color_imp.hpp
  ${inc_dir}/scene/color.hpp
  ${inc_dir}/scene/hasname.hpp
  ${inc_dir}/scene/matrix4x4.hpp
  ${inc_dir}/scene/scene_render_context.hpp
  ${inc_dir}/scene/scene.hpp
  ${inc_dir}/scene/scenenode_cast.hpp
  ${inc_dir}/scene/scenenode_properties.hpp
  ${inc_dir}/scene/scene_node.hpp
  ${inc_dir}/scene/scene_nodes.hpp
  ${inc_dir}/scene/scenenodefactory.hpp
  ${inc_dir}/scene/scenenodeparent.hpp
  ${inc_dir}/scene/transformation_properties.hpp
  ${inc_dir}/scene/transformation.hpp

  # Scene components
  ${inc_dir}/scene_components/camera_component.hpp
  ${inc_dir}/scene_components/discretetextcomponent.hpp
  ${inc_dir}/scene_components/iapp_finisher.hpp
  ${inc_dir}/scene_components/iapp_initializer.hpp
  ${inc_dir}/scene_components/iscene_control.hpp
  ${inc_dir}/scene_components/states_controller_component.hpp
  ${inc_dir}/scene_components/statescontrolleractuator_register.hpp
  ${inc_dir}/scene_components/statescontrolleractuator.hpp
  ${inc_dir}/scene_components/texteditorcomponent.hpp
  ${inc_dir}/scene_components/visibility_selector_component.hpp

  # Scene nodes
  ${inc_dir}/scene_nodes/renderizable_scene_node.hpp
  ${inc_dir}/scene_nodes/renderizables_scene_node.hpp
  ${inc_dir}/scene_nodes/scene_node_table_imp.hpp
  ${inc_dir}/scene_nodes/scene_node_table_properties.hpp
  ${inc_dir}/scene_nodes/scene_node_table_text.hpp
  ${inc_dir}/scene_nodes/scene_node_table.hpp
  ${inc_dir}/scene_nodes/scene_node_text_properties.hpp
  ${inc_dir}/scene_nodes/scene_node_text_quad.hpp
  ${inc_dir}/scene_nodes/scene_node_text.hpp
  ${inc_dir}/scene_nodes/text_base_size.hpp
  ${inc_dir}/scene_nodes/transformable_scene_node.hpp

  # Shared data
  ${inc_dir}/shareddata/address.hpp
  ${inc_dir}/shareddata/ishareable.hpp
  ${inc_dir}/shareddata/ishared_data.hpp
  ${inc_dir}/shareddata/shared_data_handler.hpp
  ${inc_dir}/shareddata/shared_data_updater.hpp
  ${inc_dir}/shareddata/shared_data_viewer.hpp

  # Simulation
  ${inc_dir}/simulation/simulationaction.hpp
  ${inc_dir}/simulation/simulationactiongroup.hpp

  # System
  ${inc_dir}/system/isystem_controller.hpp
  ${inc_dir}/system/isystem_provider.hpp
  ${inc_dir}/system/subsystem_view.hpp
  ${inc_dir}/system/subsystem_interface.hpp
  ${inc_dir}/system/system_access.hpp

  # Timer
  ${inc_dir}/time/time_point.hpp
  ${inc_dir}/time/time_view.hpp
  ${inc_dir}/time/timer_component.hpp
  ${inc_dir}/time/timer_connector.hpp
  ${inc_dir}/time/timer_data.hpp
  ${inc_dir}/time/timer_type.hpp
  ${inc_dir}/time/timer.hpp

  # Types
  ${inc_dir}/types/basic_types.hpp
  ${inc_dir}/types/property_group.hpp
  ${inc_dir}/types/scene_types.hpp
  ${inc_dir}/types/str.hpp
  ${inc_dir}/types/vector.hpp

  # Utils
  ${inc_dir}/utils/object_factory.hpp
  ${inc_dir}/utils/type_data.hpp

  # Window
  )

# Set the public directory for includes in this library. It will be
# used by the external components.
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HAF_PRIVATE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}/include" 
  SOURCES ${sources} HEADERS ${headers})

#define compile time constants
target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_ALLOW_ACCELERATION)
target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_SHOW_FPS)

# Prepare the haf libray
target_compile_definitions(${CURRENT_TARGET} PRIVATE haf_EXPORTS)
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app agloader backend backend_dev)

target_link_libraries(${CURRENT_TARGET} PUBLIC log_and_types)

# For now, we need it public for tests.
# TODO: Fix it
target_include_directories(${CURRENT_TARGET}
                           PUBLIC ${HAF_PRIVATE_INCLUDE_DIRECTORY})

include (cmake/haf_functions.cmake)

# TODO: Investigate some day if(MSVC) set_target_properties(${CURRENT_TARGET}
# PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB") endif()
addTestingDirectory(tests)
