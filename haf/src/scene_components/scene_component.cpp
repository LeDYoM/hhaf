#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/component/component_definition.hpp>

using namespace haf::core;

namespace haf::scene
{
struct SceneComponent::ComponentsRequired
{
};

SceneComponent::SceneComponent() :
    m_components{make_pimplp<ComponentsRequired>()}
{}

SceneComponent::~SceneComponent() = default;

bool SceneComponent::addRequirements(
    component::ComponentRequirements&)
{
    bool isOk{true};
    return isOk;
}

}  // namespace haf::scene
