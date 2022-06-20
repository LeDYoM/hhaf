#include <haf/include/component/component_container.hpp>
#include <htypes/include/lockablevector.hpp>

using namespace htps;

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    sptr<IComponent> getComponentFromTypeIndex(
        utils::type_index const& tindex) const
    {
        const auto v{components_.next()};
        auto iterator(v.find_if(
            v.cbegin(), v.cend(), [&tindex](sptr<IComponent> const& component) {
                return utils::type_index(typeid(*component)) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    rptr<scene::SceneNode> const attachable_;
    LockableVector<sptr<IComponent>> components_;

    ComponentContainer::ComponentContainerPrivate(
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
    p_->components_.performUpdate(
        [](sptr<IComponent> const& component) { component->update(); });
}

void ComponentContainer::clearComponents() noexcept
{
    p_->components_.clear();
}

bool ComponentContainer::addComponent(sptr<IComponent> nc)
{
    LogAsserter::log_assert(nc != nullptr, "Trying to add a nullptr component");
    p_->components_.push_back(htps::move(nc));
    return true;
}

sptr<IComponent> ComponentContainer::componentOfType(
    utils::type_index const& ti) const
{
    return p_->getComponentFromTypeIndex(ti);
}

void ComponentContainer::initialize(IComponent& component) const
{
    component.setAttachedNode(p_->attachable_);
}

}  // namespace haf::component
