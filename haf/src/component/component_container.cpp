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
        const auto v{components_.next()};
        auto iterator(v.find_if(
            v.cbegin(), v.cend(), [&tindex](sptr<Component> const& component) {
                return utils::type_index(typeid(*component)) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    rptr<scene::SceneNode> const attachable_;
    LockableVector<sptr<Component>> components_;

    explicit ComponentContainerPrivate(
        rptr<scene::SceneNode> attachable) noexcept :
        attachable_{attachable}
    {}
};

ComponentContainer::ComponentContainer(rptr<scene::SceneNode> attachable) :
    p_{make_pimplp<ComponentContainerPrivate>(attachable)}
{}

ComponentContainer::~ComponentContainer() = default;

void ComponentContainer::updateComponents()
{
    p_->components_.performUpdateBackwards(
        [](sptr<Component> const& component) { component->update(); });
}

void ComponentContainer::clearComponents() noexcept
{
    p_->components_.clear();
}

bool ComponentContainer::addComponent(sptr<Component> nc)
{
    LogAsserter::log_assert(nc != nullptr, "Trying to add a nullptr component");
    p_->components_.push_back(htps::move(nc));
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
    return p_->getComponentFromTypeIndex(ti);
}

rptr<scene::SceneNode> ComponentContainer::attachable() const noexcept
{
    return p_->attachable_;
}

void ComponentContainer::initialize(component::Component& component) const
{
    component.setAttachedNode(attachable());
}

htps::size_type ComponentContainer::components() const noexcept
{
    return p_->components_.size();
}

}  // namespace haf::component
