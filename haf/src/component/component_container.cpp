#include <haf/include/component/component_container.hpp>

#include <htypes/include/lockablevector.hpp>
#include <typeindex>

using namespace htps;

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    htps::sptr<IComponent> getComponentFromTypeIndex(
        std::type_index const& tindex) const
    {
        const auto v{components_.next()};
        auto iterator(v.find_if(
            v.cbegin(), v.cend(), [&tindex](sptr<IComponent> const& component) {
                return std::type_index(typeid(*component)) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    htps::LockableVector<htps::sptr<IComponent>> components_;
};

ComponentContainer::ComponentContainer(
    rptr<BaseClass::AttachableType> attachable) :
    BaseClass{attachable}, p_{make_pimplp<ComponentContainerPrivate>()}
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
    std::type_index const& ti) const
{
    return p_->getComponentFromTypeIndex(ti);
}

}  // namespace haf::component
