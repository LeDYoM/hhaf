HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_BOOTSTRAP_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_BOOTSTRAP_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_updater.hpp>

namespace haf::component
{
template <typename T, core::str_literal subSystemUpdateName>
class ComponentBootStrap : public Component
{
public:
    ComponentBootStrap()
    {
        ComponentUpdater::setParentSubSystem(defaultSubSystemUpdateName());
    }

    constexpr core::str_view const staticTypeName() const noexcept override
    {
        return T::StaticTypeName;
    }

    static constexpr core::str_literal StaticSubSystemUpdateName{
        subSystemUpdateName};

protected:
    using Component::Component;

    core::str_view defaultSubSystemUpdateName() const override
    {
        return core::str_view{StaticSubSystemUpdateName.cbegin()};
    }

public:
    ~ComponentBootStrap() override {}
};

}  // namespace haf::component

#endif
