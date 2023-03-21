HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_BASE_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_BASE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_requirements.hpp>

namespace haf::component
{
template <core::str_view Name, typename... Args>
class ComponentBase : public ComponentWithRequirements<Args...>
{
public:
    using BaseClass = ComponentWithRequirements<Args...>;
    static constexpr const core::str_view StaticTypeName = Name;

    constexpr core::str_view const staticTypeName() const noexcept override
    {
        return StaticTypeName;
    }
};
}  // namespace haf::component

#endif
