#include <haf/include/scene_components/camera/debug_camera_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <haf/include/scene_components/camera/camera_component.hpp>
#include <haf/include/input/keyboard_input_manager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/events/receiver.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"

using namespace haf::core;

namespace haf::scene
{
struct DebugCameraComponent::ComponentsRequired
{
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
        m_components->m_camera_component);
    return isOk;
}

void DebugCameraComponent::onAttached()
{
    m_p->m_receiver.shared_connect(
        m_components->m_camera_component,
        m_components->m_camera_component->cameraUpdated,
        make_function(this, &DebugCameraComponent::logCameraData));
}


void DebugCameraComponent::logCameraData()
{
    auto&& camera{m_components->m_camera_component};

    logger::DisplayLog::debug(
        StaticTypeName,
//        ": Camera view values:\nMode: ", (int)(m_p->m_cameraMoveType),
        "\nPosition: {", camera->Position().x, ",", camera->Position().y, ",",
        camera->Position().z, "}\nCenter: {", camera->Center().x, ",",
        camera->Center().y, ",", camera->Center().z, "}\nUp: {", camera->Up().x,
        ",", camera->Up().y, ",", camera->Up().z, "}");

    logger::DisplayLog::debug(
        StaticTypeName, ": Perspective mode: ",
        camera->cameraMode() == CameraComponent::CameraMode::Ortho
            ? "Ortho"
            : (camera->cameraMode() == CameraComponent::CameraMode::Frustum
                   ? "Frustum"
                   : "Perspective"));

    logger::DisplayLog::debug(
        StaticTypeName,
        ": Camera frustum values:\n: Left Right Bottom Top Near Far\n",
        camera->Left(), ",", camera->Right(), ",", camera->Bottom(), ",",
        camera->Top(), ",", camera->Near(), ",", camera->Far());

    logger::DisplayLog::debug(StaticTypeName,
                      ": Camera perspectve values:\n: FovY Aspect\n",
                      camera->FovY(), ",", camera->Aspect());
}

}  // namespace haf::scene
