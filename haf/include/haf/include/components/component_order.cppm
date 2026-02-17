export module haf:components:component_order;

import :component;
import :core:types;

namespace haf::component
{
class Component;
struct ComponentOrder
{
    enum class OrderPrio : core::u32
    {
        PriorityEqual = 0U,
        PriorityLess  = 1U,
        PriorityMore  = 2U
    };

    enum class OrderType : core::u32
    {
        Unordered = 0U,
        Ordered   = 1U
    };

    using Value = core::s32;
    static constexpr ComponentOrder::Value NoOrder{-1};
    Value order{NoOrder};

    static Value orderOfComponent(core::sptr<Component> const& component)
    {
        return component->componentOrder();
    }
};

}  // namespace haf::component
