#include <haf/include/component/component_container.hpp>

#include <htypes/include/lockablevector.hpp>

using namespace haf::types;

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

    htps::LockableVector<sptr<IComponent>> components_;
};

ComponentContainer::ComponentContainer(rptr<AttachableType> attachable) :
    BaseClass{attachable},
    attachable_{attachable},
    p_{make_pimplp<ComponentContainerPrivate>()}
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
    p_->components_.push_back(std::move(nc));
    return true;
}

sptr<IComponent> ComponentContainer::componentOfType(
    utils::type_index const& ti) const
{
    return p_->getComponentFromTypeIndex(ti);
}

}  // namespace haf::component
