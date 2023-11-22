#include "component_container_private.hpp"
#include "scene/scene_manager.hpp"
#include "scene_subsystems/iscene_manager subsystem.hpp"

#include "system/get_system.hpp"

using namespace haf::core;

namespace haf::component
{
sptr<Component>
ComponentContainer::ComponentContainerPrivate::getExistingComponent(
    str_view typeName) const
{
    auto iterator{
        components_.find_if([&typeName](sptr<Component> const& component) {
            return component->staticTypeName() == typeName;
        })};
    return (iterator == components_.cend()) ? nullptr : (*iterator);
}

ComponentContainer::ComponentContainerPrivate::ComponentContainerPrivate(
    rptr<scene::SceneNode> attachable) noexcept :
    attachable_{attachable},
    m_scene_manager{sys::getSystem<scene::SceneManager>(attachable)}
{}

void ComponentContainer::ComponentContainerPrivate::updateComponents(
    scene::ISceneManagerSubSystem& iSceneManagerSubSystem)
{
    for (auto&& component : components_)
    {
        component->update(iSceneManagerSubSystem);
    }
}

void ComponentContainer::ComponentContainerPrivate::clearComponents()
{
    components_.clear();
}

}  // namespace haf::component
