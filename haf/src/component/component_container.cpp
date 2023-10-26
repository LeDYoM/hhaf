#include <haf/include/component/component_container.hpp>
#include <haf/include/component/component_requirements.hpp>

#include <htypes/include/types.hpp>

#include <haf/include/scene/scene_node.hpp>

#include "scene/scene_manager.hpp"
#include "system/get_system.hpp"
#include "debug_system/debug_displayers.hpp"
#include "component/component_container_private.hpp"
#include <haf/include/log/log.hpp>

using namespace haf::core;

namespace haf::component
{
ComponentContainer::ComponentContainer(rptr<scene::SceneNode> attachable) :
    p_{make_pimplp<ComponentContainerPrivate>(attachable)}
{}

ComponentContainer::~ComponentContainer()
{
    logger::DisplayLog::debug(StaticTypeName, ": Destroying");
    clearComponents();
}

void ComponentContainer::updateComponents(
    scene::ISceneManagerSubSystem& iSceneManagerSubSystem)
{
    p_->updateComponents(iSceneManagerSubSystem);
}

void ComponentContainer::updateComponents()
{
    /*
    using scene::num_begin;
    using scene::num_end;
    using scene::SceneUpdateTime;
    using scene::toEnum;
    for (auto i{num_begin<SceneUpdateTime>()}; i < num_end<SceneUpdateTime>();
         ++i)
    {
        p_->updateComponents(toEnum<SceneUpdateTime>(i));
    }
    */
}

void ComponentContainer::clearComponents() noexcept
{
    p_->clearComponents();
}

sptr<Component> ComponentContainer::getOrCreateComponent(str_view typeName)
{
    sptr<Component> result{getExistingComponent(typeName)};
    if (!result)
    {
        result = createComponent(typeName);
        if (result)
        {
            addComponent(result);
            if (!applyRequirements(*result))
            {
                LogAsserter::log_assert(true, "Cannot create component ",
                                        typeName);
                result.reset();
            }
            else
            {
                result->setAttachedNode(p_->attachable_);
            }
        }
    }
    return result;
}

sptr<Component> ComponentContainer::attachComponent(str_view typeName)
{
    auto component{getOrCreateComponent(typeName)};

    logger::DisplayLog::debug(StaticTypeName, [this]() {
        return debug::showComponentList(p_->attachable_);
    });
    return component;
}

sptr<Component> ComponentContainer::createComponent(str_view typeName)
{
    return p_->m_scene_manager.instantiateComponent(typeName);
}

bool ComponentContainer::addComponent(sptr<Component> nc)
{
    LogAsserter::log_assert(nc != nullptr, "Trying to add a nullptr component");
    p_->components_.push_back(htps::move(nc));
    return true;
}

bool ComponentContainer::applyRequirements(Component& _thisComponent)
{
    ComponentRequirements component_requierements{*this};
    return _thisComponent.addRequirements(component_requierements);
}

sptr<Component> ComponentContainer::getExistingComponent(
    str_view typeName) const
{
    return p_->getExistingComponent(typeName);
}

size_type ComponentContainer::size() const noexcept
{
    return p_->components_.size();
}

str_view ComponentContainer::componentNameAt(size_type const index) const
{
    return (index < p_->components_.size())
        ? p_->components_[index]->staticTypeName()
        : "";
}

vector<sptr<Component>> const& ComponentContainer::components() const
{
    return p_->components_;
}

vector<sptr<Component>>::iterator ComponentContainer::begin()
{
    return p_->components_.begin();
}

vector<sptr<Component>>::const_iterator ComponentContainer::begin() const
{
    return p_->components_.begin();
}

core::vector<core::sptr<Component>>::const_iterator ComponentContainer::cbegin()
    const
{
    return p_->components_.cbegin();
}

vector<sptr<Component>>::iterator ComponentContainer::end()
{
    return p_->components_.end();
}

vector<sptr<Component>>::const_iterator ComponentContainer::end() const
{
    return p_->components_.end();
}

vector<sptr<Component>>::const_iterator ComponentContainer::cend() const
{
    return p_->components_.cend();
}

}  // namespace haf::component
