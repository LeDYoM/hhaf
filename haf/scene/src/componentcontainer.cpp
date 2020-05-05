#include "componentcontainer.hpp"

#include <hlog/include/hlog.hpp>
#include <mtypes/include/algoutils.hpp>

#include <algorithm>
#include <functional>  // std::invoke

using namespace mtps;

namespace haf::scene
{

namespace
{
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
}  // namespace

template <>
void ComponentContainerBase<true>::updateComponents()
{
    executeForAllComponents(components_, &update_impl<IComponent>);
}

template <>
void ComponentContainerBase<false>::updateComponents()
{
    components_.update();
}

}  // namespace haf::scene
