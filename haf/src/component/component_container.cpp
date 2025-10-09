#include <haf/include/component/component_container.hpp>
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/ordered_component_group.hpp>
#include <haf/include/component/unordered_component_group.hpp>

using namespace haf::core;

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    rptr<scene::SceneNode> const m_attachable;
    OrderedComponentGroup m_ordered_component_group;
    UnorderedComponentGroup m_unordered_component_group;

    explicit ComponentContainerPrivate(
        rptr<scene::SceneNode> attachable) noexcept :
        m_attachable{attachable}
    {}
};

ComponentContainer::ComponentContainer(rptr<scene::SceneNode> attachable) :
    m_p{make_pimplp<ComponentContainerPrivate>(attachable)}
{}

ComponentContainer::~ComponentContainer() = default;

void ComponentContainer::updateUnorderedComponents()
{
    for (auto index{0U}; index < m_p->m_unordered_component_group.size();
         ++index)
    {
        if (auto&& component{m_p->m_unordered_component_group[index]};
            component != nullptr)
        {
            component->update();
        }
    }
}

void ComponentContainer::updateIndexedComponent(uint32_t const index)
{
    if (auto&& component{m_p->m_unordered_component_group[index]};
        component != nullptr)
    {
        component->update();
    }
}

void ComponentContainer::clearComponents() noexcept
{
    m_p->m_ordered_component_group.clear();
    m_p->m_unordered_component_group.clear();
}

void ComponentContainer::attachComponent(sptr<Component> newComponent)
{
    applyRequirements(*newComponent);
    initialize(*newComponent);

    if (auto const order{newComponent->componentOrder()};
        order == ComponentOrder::NoOrder)
    {
        m_p->m_unordered_component_group.PushBack(htps::move(newComponent));
    }
    else
    {
        m_p->m_ordered_component_group.insertAtIndex(static_cast<u32>(order),
                                                     htps::move(newComponent));
    }
}

void ComponentContainer::applyRequirements(Component& _thisComponent)
{
    ComponentRequirements component_requierements{*this};
    _thisComponent.addRequirements(component_requierements);
}

sptr<Component> ComponentContainer::componentOfType(
    utils::type_index const& ti) const
{
    if (auto c{m_p->m_ordered_component_group.getComponentFromTypeIndex(ti)};
        c == nullptr)
    {
        return m_p->m_unordered_component_group.getComponentFromTypeIndex(ti);
    }
    else
    {
        return c;
    }
}

rptr<scene::SceneNode> ComponentContainer::attachable() const noexcept
{
    return m_p->m_attachable;
}

void ComponentContainer::initialize(component::Component& component) const
{
    component.setAttachedNode(attachable());
}

htps::size_type ComponentContainer::components() const noexcept
{
    return m_p->m_ordered_component_group.size() +
        m_p->m_unordered_component_group.size();
}

}  // namespace haf::component
