#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/component/component_definition.hpp>

using namespace haf::core;

namespace haf::scene
{
struct SceneComponent::ComponentsRequired
{
    sptr<TransformationComponent> m_transformation_component;
    sptr<DebugCameraComponent> m_debug_camera_component;
};

SceneComponent::SceneComponent() :
    m_components{make_pimplp<ComponentsRequired>()}
{}

SceneComponent::~SceneComponent() = default;

bool SceneComponent::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
//    isOk &= component_requirements.getOrCreateComponent(
//        m_components->m_transformation_component);
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_debug_camera_component);
    return isOk;
}

}  // namespace haf::scene
