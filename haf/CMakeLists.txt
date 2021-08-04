cmake_minimum_required(VERSION 3.14)
project(
  "HAF Main Library"
  VERSION 0.8.1.2
  DESCRIPTION "Host Application Framework main library"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX
)

set(CURRENT_TARGET haf)

set(src_dir src)

set(sources
  # Global
  ${src_dir}/main.cpp 
  ${src_dir}/systemprovider_init.cpp

  # Component
  ${src_dir}/component/component_container.cpp

  # FileSystem
  ${src_dir}/filesystem/fileserializer.cpp
  ${src_dir}/filesystem/filesystem.cpp
  ${src_dir}/filesystem/filesystem.hpp

  # Input
  ${src_dir}/input/input_component_base.cpp
  ${src_dir}/input/inputcomponent.cpp
  ${src_dir}/input/inputdriver_wrapper.cpp
  ${src_dir}/input/inputsystem.cpp
  ${src_dir}/input/inputsystem.hpp
  ${src_dir}/input/key_manager.cpp
  ${src_dir}/input/virtual_input_component.cpp

  # Random
  ${src_dir}/random/randomnumberscomponent.cpp
  ${src_dir}/random/randomsystem.cpp
  ${src_dir}/random/randomsystem.hpp

  # Render
  ${src_dir}/render/geometry_math.hpp
  ${src_dir}/render/renderizable_builder.cpp
  ${src_dir}/render/renderizable_internal_data.hpp
  ${src_dir}/render/renderizable_internal_functions.cpp
  ${src_dir}/render/renderizable_internal_functions.hpp
  ${src_dir}/render/renderizable.cpp
  ${src_dir}/render/renderizables.cpp
  ${src_dir}/render/rendersystem.cpp
  ${src_dir}/render/rendersystem.hpp
  ${src_dir}/render/rendertarget.cpp
  ${src_dir}/render/rendertarget.hpp
  ${src_dir}/render/vertexarray.cpp

  # Resources
  ${src_dir}/resources/bmpfont_private.cpp
  ${src_dir}/resources/bmpfont_private.hpp
  ${src_dir}/resources/bmpfont.cpp
  ${src_dir}/resources/bmpfont.hpp
  ${src_dir}/resources/bmpfontfactory.cpp
  ${src_dir}/resources/bmpfontfactory.hpp
  ${src_dir}/resources/font_utils.cpp
  ${src_dir}/resources/font_utils.hpp
  ${src_dir}/resources/resourceconfigurator.cpp
  ${src_dir}/resources/resourceretriever.cpp
  ${src_dir}/resources/resourcemanager_private.hpp
  ${src_dir}/resources/resourcemanager.cpp
  ${src_dir}/resources/resourcemanager.hpp
  ${src_dir}/resources/resources_config_data.hpp
  ${src_dir}/resources/shader.cpp
  ${src_dir}/resources/shader.hpp
  ${src_dir}/resources/texture.cpp
  ${src_dir}/resources/texture.hpp
  ${src_dir}/resources/ttfont.cpp
  ${src_dir}/resources/ttfont.hpp
  ${src_dir}/resources/ttfontinstance.cpp
  ${src_dir}/resources/ttfontinstance.hpp

  # Scene
  ${src_dir}/scene/color.cpp
  ${src_dir}/scene/matrix4x4.cpp
  ${src_dir}/scene/renderizables_scenenode.cpp
  ${src_dir}/scene/scene.cpp
  ${src_dir}/scene/scenecontroller.cpp
  ${src_dir}/scene/scenecontroller.hpp
  ${src_dir}/scene/scenemanager.cpp
  ${src_dir}/scene/scenemanager.hpp
  ${src_dir}/scene/scenenode.cpp
  ${src_dir}/scene/scenenodefactory.cpp
  ${src_dir}/scene/scenenodes.cpp
  ${src_dir}/scene/transformable.cpp
  ${src_dir}/scene/transformation.cpp

  # Scene components
  ${src_dir}/scene_components/animation.cpp
  ${src_dir}/scene_components/animationcomponent.cpp
  ${src_dir}/scene_components/app_finisher.cpp
  ${src_dir}/scene_components/app_initializer.cpp
  ${src_dir}/scene_components/discretetextcomponent.cpp
  ${src_dir}/scene_components/scenecontrol.cpp
  ${src_dir}/scene_components/scenefactory.cpp
  ${src_dir}/scene_components/scenemetrics.cpp
  ${src_dir}/scene_components/scenemetricsview.cpp
  ${src_dir}/scene_components/texteditorcomponent.cpp
  ${src_dir}/scene_components/visibility_selector_component.cpp

  # Scene nodes
  ${src_dir}/scene_nodes/renderizable_scenenode.cpp
  ${src_dir}/scene_nodes/scenenodetext.cpp
  ${src_dir}/scene_nodes/tablenode_imp.cpp
  ${src_dir}/scene_nodes/text_table_node.cpp
  ${src_dir}/scene_nodes/textquad.cpp

  # Shared data
  ${src_dir}/shareddata/address.cpp
  ${src_dir}/shareddata/shareddata.cpp
  ${src_dir}/shareddata/shareddatasystem.cpp
  ${src_dir}/shareddata/shareddatasystem.hpp

  # Simulation
  ${src_dir}/simulation/simulationsystem_private.hpp
  ${src_dir}/simulation/simulationsystem.cpp
  ${src_dir}/simulation/simulationsystem.hpp

  # System
  ${src_dir}/system/get_system.cpp
  ${src_dir}/system/get_system.hpp
  ${src_dir}/system/get_systemprovider.cpp
  ${src_dir}/system/get_systemprovider.hpp
  ${src_dir}/system/init_system_options.hpp
  ${src_dir}/system/system_options_init.hpp
  ${src_dir}/system/systemaccess.cpp
  ${src_dir}/system/systembase.cpp
  ${src_dir}/system/systembase.hpp
  ${src_dir}/system/systemcontroller.cpp
  ${src_dir}/system/systemcontroller.hpp
  ${src_dir}/system/systemdatawrappercreator.hpp
  ${src_dir}/system/systemprovider.cpp
  ${src_dir}/system/systemprovider.hpp

  # Time
  ${src_dir}/time/timepoint.cpp
  ${src_dir}/time/timer.cpp
  ${src_dir}/time/timercomponent.cpp
  ${src_dir}/time/timesystem.cpp
  ${src_dir}/time/timesystem.hpp
  ${src_dir}/time/timeview.cpp

  # Window
  ${src_dir}/window/window_properties.cpp
  ${src_dir}/window/window.cpp
  ${src_dir}/window/window.hpp
  )

set(inc_dir include/haf/include)

set(headers
  # Global
  ${inc_dir}/haf_export.hpp

  # Component
  ${inc_dir}/component/component_container.hpp
  ${inc_dir}/component/icomponent_mixin.hpp
  ${inc_dir}/component/icomponent.hpp

  # File system
  ${inc_dir}/filesystem/fileserializer.hpp
  ${inc_dir}/filesystem/path.hpp

  # Input
  ${inc_dir}/input/input_component_base.hpp
  ${inc_dir}/input/inputcomponent.hpp
  ${inc_dir}/input/inputdriver_wrapper.hpp
  ${inc_dir}/input/key_manager.hpp
  ${inc_dir}/input/key.hpp
  ${inc_dir}/input/virtual_input_component.hpp

  # Random
  ${inc_dir}/random/randomnumberscomponent.hpp

  # Render
  ${inc_dir}/render/fig_type.hpp
  ${inc_dir}/render/primitivetype.hpp
  ${inc_dir}/render/renderdata.hpp
  ${inc_dir}/render/renderizable_builder_data.hpp
  ${inc_dir}/render/renderizable_builder.hpp
  ${inc_dir}/render/renderizable_modifier_context.hpp
  ${inc_dir}/render/renderizable.hpp
  ${inc_dir}/render/renderizables.hpp
  ${inc_dir}/render/vertex.hpp
  ${inc_dir}/render/vertexarray.hpp

  # Resources
  ${inc_dir}/resources/ifont.hpp
  ${inc_dir}/resources/resourceconfigurator.hpp
  ${inc_dir}/resources/resourceretriever.hpp
  ${inc_dir}/resources/ishader.hpp
  ${inc_dir}/resources/itexture.hpp
  ${inc_dir}/resources/ittfont.hpp

  # Scene
  ${inc_dir}/scene/color_imp.hpp
  ${inc_dir}/scene/color.hpp
  ${inc_dir}/scene/hasname.hpp
  ${inc_dir}/scene/matrix4x4.hpp
  ${inc_dir}/scene/renderizables_scenenode.hpp
  ${inc_dir}/scene/scene.hpp
  ${inc_dir}/scene/scenenode_cast.hpp
  ${inc_dir}/scene/scenenode_properties.hpp
  ${inc_dir}/scene/scenenode.hpp
  ${inc_dir}/scene/scenenodefactory.hpp
  ${inc_dir}/scene/scenenodeparent.hpp
  ${inc_dir}/scene/scenenodes.hpp
  ${inc_dir}/scene/transformable_scenenode.hpp
  ${inc_dir}/scene/transformable.hpp
  ${inc_dir}/scene/transformation_properties.hpp
  ${inc_dir}/scene/transformation.hpp

  # Scene components
  ${inc_dir}/scene_components/animabletypes.hpp
  ${inc_dir}/scene_components/animation.hpp
  ${inc_dir}/scene_components/animationcomponent.hpp
  ${inc_dir}/scene_components/app_finisher.hpp
  ${inc_dir}/scene_components/app_initializer.hpp
  ${inc_dir}/scene_components/discretetextcomponent.hpp
  ${inc_dir}/scene_components/ipropertyanimation.hpp
  ${inc_dir}/scene_components/scenecontrol.hpp
  ${inc_dir}/scene_components/scenefactory.hpp
  ${inc_dir}/scene_components/scenemetrics.hpp
  ${inc_dir}/scene_components/scenemetricsview.hpp
  ${inc_dir}/scene_components/statescontroller.hpp
  ${inc_dir}/scene_components/statescontrolleractuator.hpp
  ${inc_dir}/scene_components/texteditorcomponent.hpp
  ${inc_dir}/scene_components/visibility_selector_component.hpp

  # Scene nodes
  ${inc_dir}/scene_nodes/renderizable_scenenode.hpp
  ${inc_dir}/scene_nodes/scene_node_size.hpp
  ${inc_dir}/scene_nodes/scenenodetext_properties.hpp
  ${inc_dir}/scene_nodes/scenenodetext.hpp
  ${inc_dir}/scene_nodes/tablenode_imp.hpp
  ${inc_dir}/scene_nodes/tablenode_properties.hpp
  ${inc_dir}/scene_nodes/tablenode.hpp
  ${inc_dir}/scene_nodes/text_table_node.hpp
  ${inc_dir}/scene_nodes/textquad.hpp

  # Shared data
  ${inc_dir}/shareddata/address.hpp
  ${inc_dir}/shareddata/ishareable.hpp
  ${inc_dir}/shareddata/shareddata.hpp
  ${inc_dir}/shareddata/shareddataupdater.hpp
  ${inc_dir}/shareddata/shareddataviewer.hpp

  # Simulation
  ${inc_dir}/simulation/simulationaction.hpp
  ${inc_dir}/simulation/simulationactiongroup.hpp

  # System
  ${inc_dir}/system/datawrappercreator.hpp
  ${inc_dir}/system/idatawrapper.hpp
  ${inc_dir}/system/isystemcontroller.hpp
  ${inc_dir}/system/isystemprovider.hpp
  ${inc_dir}/system/systemaccess.hpp

  # Timer
  ${inc_dir}/time/timepoint.hpp
  ${inc_dir}/time/timer.hpp
  ${inc_dir}/time/timercomponent.hpp
  ${inc_dir}/time/timerconnector.hpp
  ${inc_dir}/time/timertype.hpp
  ${inc_dir}/time/timeview.hpp

  # Utils
  ${inc_dir}/utils/attachable_manager.hpp
  ${inc_dir}/utils/attachable.hpp
  ${inc_dir}/utils/object_factory.hpp

  # Window
  ${inc_dir}/window/window_properties.hpp
  )

# Set the public directory for includes in this library. It will be
# used by the external components.
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HAF_PRIVATE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

build_lib_component(EXPORT_ALL HEADER_DIRECTORY "${PROJECT_SOURCE_DIR}/include" 
  SOURCES ${sources} HEADERS ${headers})

# Prepare the haf libray
target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_ALLOW_ACCELERATION)
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
