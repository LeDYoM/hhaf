HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_ORDER_HPP
#define HAF_COMPONENT_COMPONENT_ORDER_HPP

#include <haf/include/core/types.hpp>

namespace haf::component
{
struct ComponentOrder
{
    using Value = core::s32;
    static constexpr ComponentOrder::Value NoOrder{-1};
    Value Order{NoOrder};
};

}  // namespace haf::component

#endif
