#include <haf/include/component/component_container.hpp>
#include <haf/include/component/component_requirements.hpp>

#include <htypes/include/types.hpp>

#include <haf/include/scene/scene_node.hpp>

#include "scene/scene_manager.hpp"
#include "system/get_system.hpp"
#include "debug_system/debug_displayers.hpp"

using namespace htps;

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    sptr<Component> getExistingComponent(core::str_view typeName) const
    {
        auto iterator{
            components_.find_if([&typeName](sptr<Component> const& component) {
                return component->staticTypeName() == typeName;
            })};
        return (iterator == components_.cend()) ? nullptr : (*iterator);
    }

    rptr<scene::SceneNode> const attachable_;
    scene::SceneManager& m_scene_manager;
    vector<sptr<Component>> components_;

    ComponentContainerPrivate(rptr<scene::SceneNode> attachable) noexcept :
        attachable_{attachable},
        m_scene_manager{sys::getSystem<scene::SceneManager>(attachable)}
    {}

    void updateComponentsBackwards()
    {
        components_.for_each_backwards([](sptr<Component> const& component) {
            component->updateComponent();
        });
    }

    void clearComponents() { components_.clear(); }
    void clearComponentsBackwards()
    {
        while (!components_.empty())
        {
            components_.pop_back();
        }
    }
};

ComponentContainer::ComponentContainer(rptr<scene::SceneNode> attachable) :
    p_{make_pimplp<ComponentContainerPrivate>(attachable)}
{}

ComponentContainer::~ComponentContainer()
{
    DisplayLog::debug(StaticTypeName, ": Destroying");
    p_->clearComponentsBackwards();
}

void ComponentContainer::updateComponents()
{
    p_->updateComponentsBackwards();
}

void ComponentContainer::clearComponents() noexcept
{
    p_->clearComponentsBackwards();
}

sptr<Component> ComponentContainer::getOrCreateComponent(
    core::str_view typeName)
{
    core::sptr<Component> result{componentOfType(typeName)};
    if (!result)
    {
        result = createComponent(typeName);
        if (result)
        {
            if (applyRequirements(*result))
            {
                addComponent(result);
            }
            else
            {
                result.reset();
            }
        }
    }
    return result;
}

sptr<Component> ComponentContainer::attachComponent(core::str_view typeName)
{
    auto component{getOrCreateComponent(typeName)};
    DisplayLog::debug(StaticTypeName, [this]() {
        return debug::showComponentList(p_->attachable_);
    });
    return component;
}

sptr<Component> ComponentContainer::createComponent(core::str_view typeName)
{
    return p_->m_scene_manager.instantiateComponent(typeName);
}

bool ComponentContainer::addComponent(sptr<Component> nc)
{
    LogAsserter::log_assert(nc != nullptr, "Trying to add a nullptr component");
    nc->setAttachedNode(p_->attachable_);
    p_->components_.push_back(htps::move(nc));
    return true;
}

bool ComponentContainer::applyRequirements(Component& _thisComponent)
{
    ComponentRequirements component_requierements{*this};
    return _thisComponent.addRequirements(component_requierements);
}

sptr<Component> ComponentContainer::componentOfType(
    core::str_view typeName) const
{
    return p_->getExistingComponent(typeName);
}

core::size_type ComponentContainer::components() const noexcept
{
    return p_->components_.size();
}

core::str_view ComponentContainer::componentNameAt(
    core::size_type const index) const
{
    return (index < p_->components_.size())
        ? p_->components_[index]->staticTypeName()
        : "";
}

}  // namespace haf::component
