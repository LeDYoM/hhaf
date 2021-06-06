cmake_minimum_required(VERSION 3.14)
project(
  "HAF Main Library"
  VERSION 0.8.1.2
  DESCRIPTION "Host Application Framework main library"
  # [HOMEPAGE_URL <url-string>]
  LANGUAGES CXX
)

set(src_dir src)

set(_SOURCES
  # Global
  ${src_dir}/main.cpp 
  ${src_dir}/systemprovider_init.cpp

  # FileSystem
  ${src_dir}/filesystem/fileserializer.cpp
  ${src_dir}/filesystem/filesystem.cpp
  ${src_dir}/filesystem/filesystem.hpp

  # Input
  ${src_dir}/input/input_component_base.cpp
  ${src_dir}/input/inputcomponent.cpp
  ${src_dir}/input/inputdriver.cpp
  ${src_dir}/input/inputsystem.cpp
  ${src_dir}/input/inputsystem.hpp
  ${src_dir}/input/key_manager.cpp
  ${src_dir}/input/virtual_input_component.cpp

  # Random
  ${src_dir}/random/randomnumberscomponent.cpp
  ${src_dir}/random/randomsystem.cpp
  ${src_dir}/random/randomsystem.hpp

  # Render
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
  ${src_dir}/resources/iresourceconfigurator.cpp
  ${src_dir}/resources/iresourceretriever.cpp
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
  ${src_dir}/scene/componentcontainer_no_update.cpp
  ${src_dir}/scene/componentcontainer_update.cpp
  ${src_dir}/scene/componentcontainer.cpp
  ${src_dir}/scene/interface_getter.cpp
  ${src_dir}/scene/matrix4x4.cpp
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
  ${src_dir}/scene_components/visibility_selector.cpp

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
  ${src_dir}/system/interfaceaccess_imp.hpp
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

file(GLOB_RECURSE _HEADERS "include/*.hpp")

set(CURRENT_TARGET haf)

# Set the public directory for includes in this library. It will be
# used by the external components.
set(HAF_PUBLIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(HAF_PRIVATE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Prepare the haf libray
add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS})
target_compile_definitions(${CURRENT_TARGET} PRIVATE HAF_ALLOW_ACCELERATION)
target_compile_definitions(${CURRENT_TARGET} PRIVATE haf_EXPORTS)
set_compile_warning_level_and_cxx_properties(${CURRENT_TARGET})

# For now, export all simbols
set_target_properties(${CURRENT_TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS
                                                   true)

# External users of the library will need to include from this directory.
target_include_directories(${CURRENT_TARGET}
                           PUBLIC ${HAF_PUBLIC_INCLUDE_DIRECTORY})

# For now, we need it public for tests.
# TODO: Fix it
target_include_directories(${CURRENT_TARGET}
                           PUBLIC ${HAF_PRIVATE_INCLUDE_DIRECTORY})

target_include_directories(${CURRENT_TARGET}
                           PUBLIC "${HAF_PRIVATE_INCLUDE_DIRECTORY}/../")

target_compile_definitions(${CURRENT_TARGET} PRIVATE haf_EXPORTS)

include (cmake/haf_functions.cmake)

#add_subdirectory(filesystem)
#add_subdirectory(render)
#add_subdirectory(resources)
#add_subdirectory(scene)
#add_subdirectory(scene_components)
#add_subdirectory(scene_nodes)
#add_subdirectory(time)
#add_subdirectory(input)
#add_subdirectory(random)
#add_subdirectory(simulation)
#add_subdirectory(system)
#add_subdirectory(shareddata)
#add_subdirectory(window)

# Internal libraries necessary for the library only.
target_link_libraries(${CURRENT_TARGET} PRIVATE hosted_app agloader backend backend_dev)
target_link_libraries(${CURRENT_TARGET} PUBLIC log_and_types)


# TODO: Investigate some day if(MSVC) set_target_properties(${CURRENT_TARGET}
# PROPERTIES LINK_FLAGS "${LINK_FLAGS} /NODEFAULTLIB") endif()

add_subdirectory(tests)
