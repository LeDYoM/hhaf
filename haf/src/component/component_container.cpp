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
        const auto v{m_components.next()};
        auto iterator(v.find_if(
            v.cbegin(), v.cend(), [&tindex](sptr<Component> const& component) {
                return utils::type_index(typeid(*component)) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    rptr<scene::SceneNode> const m_attachable;
    LockableVector<sptr<Component>> m_components;

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
    m_p->m_components.performUpdate(
        [](sptr<Component> const& component) { component->update(); });
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
    return addComponent(htps::move(newComponent));
}

bool ComponentContainer::addComponent(sptr<Component> nc)
{
    LogAsserter::log_assert(nc != nullptr, "Trying to add a nullptr component");
    m_p->m_components.push_back(htps::move(nc));
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
