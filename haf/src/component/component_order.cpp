#include <haf/include/component/component_order.hpp>
#include <haf/include/component/component.hpp>

using namespace haf::core;

namespace haf::component
{
ComponentOrder::Value ComponentOrder::orderOfComponent(
    sptr<Component> const& component)
{
    return component->componentOrder();
}

}  // namespace haf::component
