#include <haf/include/component/component_container.hpp>
#include <haf/include/component/component_requirements.hpp>
#include <htypes/include/lockable_vector.hpp>

using namespace htps;

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    sptr<Component> getComponentFromTypeIndex(
        utils::type_index const& tindex) const
    {
        auto iterator(m_components.find_if(
            m_components.cbegin(), m_components.cend(), [&tindex](sptr<Component> const& component) {
                return utils::type_index(typeid(*component)) == tindex;
            }));
        return (iterator == m_components.cend()) ? nullptr : (*iterator);
    }

    rptr<scene::SceneNode> const m_attachable;
    vector<sptr<Component>> m_components;

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
    for(auto index{0U}; index < m_p->m_components.size(); ++index)
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
    m_p->m_components.clear();
}

bool ComponentContainer::attachComponent(sptr<Component> newComponent)
{
    applyRequirements(*newComponent);
    initialize(*newComponent);

    if (auto const order{newComponent->componentOrder()}; order == ComponentOrder::NoOrder)
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
