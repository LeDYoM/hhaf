HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_ORDER_HPP
#define HAF_COMPONENT_COMPONENT_ORDER_HPP

#include <haf/include/core/types.hpp>

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

    static Value orderOfComponent(core::sptr<Component> const& component);
};

}  // namespace haf::component

#endif
