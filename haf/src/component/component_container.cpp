#include <haf/include/component/component_container.hpp>
#include <typeindex>

using namespace htps;

namespace haf::component
{

void ComponentContainer::updateComponents()
{
    components_.performUpdate(
        [](sptr<IComponent> const& component) { component->update(); });
}

void ComponentContainer::clearComponents() noexcept
{
    components_.clear();
}

std::type_index tindexOf(sptr<IComponent> const& c)
{
    return std::type_index(typeid(*c));
}

htps::sptr<IComponent> getComponentFromTypeIndex(
    LockableVector<sptr<IComponent>> const& components,
    std::type_index const& tindex)
{
    const auto v{components.next()};
    auto iterator(v.find_if(v.cbegin(), v.cend(),
                            [&tindex](sptr<IComponent> const& component) {
                                return tindexOf(component) == tindex;
                            }));
    return (iterator == v.cend()) ? nullptr : (*iterator);
}

htps::sptr<IComponent> ComponentContainer::componentOfType(
    std::type_index const& ti) const
{
    return getComponentFromTypeIndex(components_, ti);
}

bool ComponentContainer::addComponent(sptr<IComponent> nc)
{
    LogAsserter::log_assert(nc != nullptr, "Trying to add a nullptr component");
    components_.emplace_back(std::move(nc));
    return true;
}

}  // namespace haf::component
