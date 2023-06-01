#include <haf/include/scene_components/debug_camera_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/input/keyboard_input_component.hpp>

#include <hlog/include/hlog.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"
#include "resources/resource_manager.hpp"

using namespace haf::core;
using namespace haf::input;

namespace haf::scene
{
struct DebugCameraComponent::ComponentsRequired
{
    sptr<input::KeyboardInputComponent> m_keyboard_input_component;
    sptr<CameraComponent> m_camera_component;
};

struct DebugCameraComponent::PrivateComponentData
{
    evt::ireceiver m_receiver;
};

DebugCameraComponent::DebugCameraComponent() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

DebugCameraComponent::~DebugCameraComponent() = default;

bool DebugCameraComponent::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_keyboard_input_component);
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_camera_component);
    return isOk;
}

void DebugCameraComponent::onAttached()
{
    Speed = 0.01F;
    m_p->m_receiver.shared_connect(
        m_components->m_keyboard_input_component,
        m_components->m_keyboard_input_component->KeyPressed,
        make_function(this, &DebugCameraComponent::moveCamera));

    m_p->m_receiver.shared_connect(
        m_components->m_camera_component,
        m_components->m_camera_component->cameraUpdated,
        make_function(this, &DebugCameraComponent::logCameraData));
}

void DebugCameraComponent::moveCamera(Key const& key)
{
    auto&& camera{m_components->m_camera_component};
    switch (key)
    {
        case Key::T:
            camera->Position.modify().moveZ(Speed());
            break;
        case Key::G:
            camera->Position.modify().moveZ(-Speed());
            break;
        case Key::H:
            camera->Position.modify().moveY(Speed());
            break;
        case Key::F:
            camera->Position.modify().moveY(-Speed());
            break;
        case Key::R:
            camera->Position.modify().moveX(Speed());
            break;
        case Key::Y:
            camera->Position.modify().moveX(-Speed());
            break;
        case Key::W:
            camera->Center.modify().moveZ(Speed());
            break;
        case Key::S:
            camera->Center.modify().moveZ(-Speed());
            break;
        case Key::A:
            camera->Center.modify().moveY(Speed());
            break;
        case Key::D:
            camera->Center.modify().moveY(-Speed());
            break;
        case Key::Q:
            camera->Center.modify().moveX(Speed());
            break;
        case Key::E:
            camera->Center.modify().moveX(-Speed());
            break;
        case Key::I:
            camera->Up.modify().moveZ(Speed());
            break;
        case Key::K:
            camera->Up.modify().moveZ(-Speed());
            break;
        case Key::J:
            camera->Up.modify().moveY(Speed());
            break;
        case Key::L:
            camera->Up.modify().moveY(-Speed());
            break;
        case Key::U:
            camera->Up.modify().moveX(Speed());
            break;
        case Key::O:
            camera->Up.modify().moveX(-Speed());
            break;
        case Key::Num1:
            camera->Left.modify() += Speed();
            break;
        case Key::Num2:
            camera->Left.modify() -= Speed();
            break;
        case Key::Num3:
            camera->Right.modify() += Speed();
            break;
        case Key::Num4:
            camera->Right.modify() -= Speed();
            break;
        case Key::Num5:
            camera->Bottom.modify() += Speed();
            break;
        case Key::Num6:
            camera->Bottom.modify() -= Speed();
            break;
        case Key::Num7:
            camera->Top.modify() += Speed();
            break;
        case Key::Num8:
            camera->Top.modify() -= Speed();
            break;
        case Key::Num9:
            camera->Near.modify() += Speed();
            break;
        case Key::Num0:
            camera->Near.modify() -= Speed();
            break;
        case Key::F1:
            camera->Far.modify() += Speed();
            break;
        case Key::F2:
            camera->Far.modify() -= Speed();
            break;
        case Key::F3:
            camera->cameraMode = CameraComponent::CameraMode::Ortho;
            break;
        case Key::F4:
            camera->cameraMode = CameraComponent::CameraMode::Frustum;
            break;
        case Key::F5:
            camera->cameraMode = CameraComponent::CameraMode::Perspective;
            break;
    }
}

void DebugCameraComponent::logCameraData()
{
    auto&& camera{m_components->m_camera_component};

    DisplayLog::debug(
        StaticTypeName, ": Camera view updated. New values:\nPosition: {",
        camera->Position().x, ",", camera->Position().y, ",",
        camera->Position().z, "}\nCenter: {", camera->Center().x, ",",
        camera->Center().y, ",", camera->Center().z, "}\nUp: {", camera->Up().x,
        ",", camera->Up().y, ",", camera->Up().z, "}");

    DisplayLog::debug(
        StaticTypeName, ": Mode: ",
        camera->cameraMode() == CameraComponent::CameraMode::Ortho
            ? "Ortho"
            : (camera->cameraMode() == CameraComponent::CameraMode::Frustum
                   ? "Frustum"
                   : "Perspective"));

    DisplayLog::debug(StaticTypeName,
                      ": Camera perspectve updated. New values:\n: Left Right "
                      "Bottom Top Near Far\n",
                      camera->Left(), ",", camera->Right(), ",",
                      camera->Bottom(), ",", camera->Top(), ",", camera->Near(),
                      ",", camera->Far());
}

}  // namespace haf::scene
