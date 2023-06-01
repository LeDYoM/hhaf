#include "component_register.hpp"
#include "scene_manager.hpp"

#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/scene_components/global_transformation_component.hpp>
#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/scene_components/debug_camera_component.hpp>

#include <haf/include/input/keyboard_input_component.hpp>

#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/render/material_data_component.hpp>

namespace haf::scene
{
ComponentRegister::ComponentRegister(SceneManager& scene_manager) :
    m_scene_manager{scene_manager}
{}

bool ComponentRegister::operator()()
{
    bool ok{true};
    ok &= m_scene_manager.registerComponent<SceneComponent>();
    ok &= m_scene_manager.registerComponent<GlobalTransformationComponent>();
    ok &= m_scene_manager.registerComponent<TransformationComponent>();
    ok &= m_scene_manager.registerComponent<CameraComponent>();
    ok &= m_scene_manager.registerComponent<DebugCameraComponent>();

    ok &= m_scene_manager.registerComponent<input::KeyboardInputComponent>();

    ok &= m_scene_manager.registerComponent<render::MeshRenderComponent>();
    ok &= m_scene_manager.registerComponent<render::MaterialDataComponent>();

    return ok;
}

}  // namespace haf::scene
