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

void ComponentContainer::updateComponents()
{
    for (auto index{0U}; index < m_p->m_components.size(); ++index)
    {
        if (auto component{m_p->m_components[index]}; component != nullptr)
        {
            m_p->m_components[index]->update();
        }
    }
}

void ComponentContainer::updateIndexedComponent(uint32_t const index)
{
    (void)(index);
}

void ComponentContainer::clearComponents() noexcept
{
    m_p->m_ordered_component_group.clear();
    m_p->m_unordered_component_group.clear();
}

bool ComponentContainer::attachComponent(sptr<Component> newComponent)
{
    applyRequirements(*newComponent);
    initialize(*newComponent);

    if (auto const order{newComponent->componentOrder()};
        order == ComponentOrder::NoOrder)
    {
        m_p->m_components.push_back(htps::move(newComponent));
    }
    else
    {
        m_p->m_components.push_back(htps::move(newComponent));
        //        auto components{m_p->m_components.next()};
        //        if (components.size() < order)
        {
            //            m_p->m_components.current().
        }
    }

    return true;
}

void ComponentContainer::applyRequirements(Component& _thisComponent)
{
    ComponentRequirements component_requierements{*this};
    _thisComponent.addRequirements(component_requierements);
}

sptr<Component> ComponentContainer::componentOfType(
    utils::type_index const& ti) const
{
    return m_p->getComponentFromTypeIndex(ti);
    
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
    return m_p->m_components.size();
}

}  // namespace haf::component
