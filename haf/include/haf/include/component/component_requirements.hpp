HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_REQUIREMENTS_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_REQUIREMENTS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_container.hpp>

namespace haf::component
{
class ComponentRequirements
{
public:
    explicit ComponentRequirements(ComponentContainer& component_container) :
        m_component_container{component_container}
    {}

    template <typename T>
    bool getOrCreateComponent(core::sptr<T>& element)
    {
        if (element == nullptr)
        {
            if constexpr (requires { T::StaticTypeName; })
            {
                auto component{m_component_container.safeComponentConversion<T>(
                    m_component_container.getOrCreateComponent(
                        T::StaticTypeName))};
                element = component;
            }
        }

        return element != nullptr;
    }

private:
    ComponentContainer& m_component_container;
};
}  // namespace haf::component

#endif
