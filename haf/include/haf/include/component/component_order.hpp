HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_ORDER_HPP
#define HAF_COMPONENT_COMPONENT_ORDER_HPP

#include <haf/include/core/types.hpp>

namespace haf::component
{
struct ComponentOrder
{
    enum class OrderPrio : core::u32
    {
        PriorityEqual = 0U,
        PriorityLess = 1U,
        PriorityMore = 2U,
    };
    using Value = core::s32;
    static constexpr ComponentOrder::Value NoOrder{-1};
    Value Order{NoOrder};
};

}  // namespace haf::component

#endif
