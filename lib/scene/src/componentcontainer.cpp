#include "componentcontainer.hpp"

#include <lib/include/liblog.hpp>
#include <mtypes/include/algoutils.hpp>

#include <algorithm>
#include <functional> // std::invoke
#include <memory>     // std::addressof

namespace lib::scene
{
namespace
{
inline std::type_index tindexOf(const sptr<IComponent> &c)
{
    return std::type_index(typeid(*c));
}

inline sptr<IComponent> getComponentFromTypeIndex(const std::type_index &tindex, const vector_shared_pointers<IComponent> &v)
{
    auto iterator(std::find_if(v.cbegin(), v.cend(), [&tindex](const sptr<IComponent> &component) { return tindexOf(component) == tindex; }));
    return (iterator == v.cend()) ? nullptr : (*iterator);
}
} // namespace

bool ComponentContainer::addComponent(sptr<IComponent> nc)
{
    log_assert(nc != nullptr, "Trying to add a nullptr component");
    m_components.emplace_back(std::move(nc));
    return true;
}

template <typename T>
void update_impl(const sptr<T> p)
{
    std::invoke(&T::update, p);
}

template <typename LCKV, typename F>
void executeForAllComponents(LCKV &components, F &&f)
{
    components.update();

    if (!components.current().empty())
    {
        for_each_all(components.current(),
                     std::forward<F>(f));
        components.update();
    }
}

void ComponentContainer::updateComponents()
{
    executeForAllComponents(m_components,
                            &update_impl<IComponent>);
}

const sptr<IComponent> ComponentContainer::componentOfType(const std::type_index &ti) const
{
    return getComponentFromTypeIndex(ti, m_components.next());
}
} // namespace lib::scene
