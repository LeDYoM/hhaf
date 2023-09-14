#include <haf/include/scene_components/camera/move_camera_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <haf/include/scene_components/camera/camera_component.hpp>
#include <haf/include/input/keyboard_input_manager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/events/receiver.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"

using namespace haf::core;
using namespace haf::input;

namespace haf::scene
{
struct MoveCameraComponent::ComponentsRequired
{
    sptr<CameraComponent> m_camera_component;
};

enum class CameraMoveType
{
    Mode0 = 0,
    Mode1 = 1,
    Mode2 = 2,
    Mode3 = 3
};

struct MoveCameraComponent::PrivateComponentData
{
    evt::ireceiver m_receiver;
    CameraMoveType m_cameraMoveType{CameraMoveType::Mode0};
};

MoveCameraComponent::MoveCameraComponent() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

MoveCameraComponent::~MoveCameraComponent() = default;

bool MoveCameraComponent::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_camera_component);
    return isOk;
}

void MoveCameraComponent::onAttached()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .KeyPressed().connect(
            make_function(this, &MoveCameraComponent::moveCamera));
    Speed = 0.01F;
}

void MoveCameraComponent::moveCamera(Key const& key)
{
    auto&& camera{m_components->m_camera_component};
    switch (key)
    {
        case Key::Num0:
            m_p->m_cameraMoveType = CameraMoveType::Mode0;
            camera->Position.modify();
            break;
        case Key::Num1:
            m_p->m_cameraMoveType = CameraMoveType::Mode1;
            camera->Position.modify();
            break;
        case Key::Num2:
            m_p->m_cameraMoveType = CameraMoveType::Mode2;
            camera->Position.modify();
            break;
        case Key::Num3:
            m_p->m_cameraMoveType = CameraMoveType::Mode3;
            camera->Position.modify();
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
        default:
            break;
    }

    switch (m_p->m_cameraMoveType)
    {
        case CameraMoveType::Mode0:
        {
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
                default:
                    break;
            }
        }
        break;
        case CameraMoveType::Mode1:
        {
            switch (key)
            {
                case Key::Q:
                    camera->Left.modify() += Speed();
                    break;
                case Key::W:
                    camera->Left.modify() -= Speed();
                    break;
                case Key::E:
                    camera->Right.modify() += Speed();
                    break;
                case Key::R:
                    camera->Right.modify() -= Speed();
                    break;
                case Key::A:
                    camera->Bottom.modify() += Speed();
                    break;
                case Key::S:
                    camera->Bottom.modify() -= Speed();
                    break;
                case Key::D:
                    camera->Top.modify() += Speed();
                    break;
                case Key::F:
                    camera->Top.modify() -= Speed();
                    break;
                case Key::Z:
                    camera->Near.modify() += Speed();
                    break;
                case Key::X:
                    camera->Near.modify() -= Speed();
                    break;
                case Key::C:
                    camera->Far.modify() += Speed();
                    break;
                case Key::V:
                    camera->Far.modify() -= Speed();
                    break;
                case Key::T:
                    camera->FovY.modify() += Speed();
                    break;
                case Key::Y:
                    camera->FovY.modify() -= Speed();
                    break;
                case Key::G:
                    camera->Aspect.modify() += Speed();
                    break;
                case Key::H:
                    camera->Aspect.modify() -= Speed();
                    break;
                default:
                    break;
            }
        }
        break;
        case CameraMoveType::Mode2:
        {
        }
        break;
        case CameraMoveType::Mode3:
        {
            switch (key)
            {
                case Key::W:
                    camera->Center.modify().moveZ(-Speed());
                    camera->Position.modify().moveZ(-Speed());
                    break;
                case Key::S:
                    camera->Center.modify().moveZ(Speed());
                    camera->Position.modify().moveZ(Speed());
                    break;
                case Key::A:
                    camera->Center.modify().moveX(-Speed());
                    camera->Position.modify().moveX(-Speed());
                    break;
                case Key::D:
                    camera->Center.modify().moveX(Speed());
                    camera->Position.modify().moveX(Speed());
                    break;
                case Key::Q:
                    camera->Center.modify().moveY(-Speed());
                    camera->Position.modify().moveY(-Speed());
                    break;
                case Key::Z:
                    camera->Center.modify().moveY(Speed());
                    camera->Position.modify().moveY(Speed());
                    break;
                default:
                    break;
            }
        }
        break;
    }
}

}  // namespace haf::scene
