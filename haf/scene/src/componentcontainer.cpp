#include "componentcontainer.hpp"

#include <hlog/include/hlog.hpp>
#include <mtypes/include/algoutils.hpp>

#include <algorithm>
#include <functional>  // std::invoke
#include <memory>      // std::addressof

using namespace mtps;

namespace haf::scene
{
namespace
{
}  // namespace

template <typename T>
void update_impl(const sptr<T> p)
{
    std::invoke(&T::update, p);
}

template <typename LCKV, typename F>
void executeForAllComponents(LCKV& components, F&& f)
{
    components.update();

    if (!components.current().empty())
    {
        for_each_all(components.current(), std::forward<F>(f));
        components.update();
    }
}

void ComponentContainer::updateComponents()
{
    executeForAllComponents(m_components, &update_impl<IComponent>);
}

}  // namespace haf::scene
