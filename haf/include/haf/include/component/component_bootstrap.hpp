HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_BOOTSTRAP_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_BOOTSTRAP_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty_state.hpp>
#include <haf/include/component/component.hpp>

namespace haf::component
{
template <typename T>
class ComponentBootStrap : public Component
{
public:
    constexpr core::str_view const staticTypeName() const noexcept override
    {
        return T::StaticTypeName;
    }

protected:
    using Component::Component;

public:
    ~ComponentBootStrap() override{};
};

}  // namespace haf::component

#endif
