HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_UPDATERS_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_UPDATERS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty_state.hpp>
#include <haf/include/component/component_updater.hpp>

namespace haf::component
{
enum class UpdateTime : core::u32
{
    Controller  = 0U,
    BeginUpdate = 1U,
    EndUpdate   = 2U,
    Render      = 3U,
    Last        = 4
};

class ComponentUpdaters
{
protected:
    using UpdateFunction = ComponentUpdater::UpdateFunction;
    using UpdateProperty = ComponentUpdater::UpdateProperty;
    using UpdateAction   = ComponentUpdater::UpdateAction;

    ComponentUpdater& get(UpdateTime const updateTime);

private:
    core::array<ComponentUpdater, 4U> m_component_updaters;
};

}  // namespace haf::component

#endif
