HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_REQUIREMENTS_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_REQUIREMENTS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_container.hpp>

template <typename T>
concept HasStaticTypeName = requires
{
    T::StaticTypeName;
};

namespace haf::component
{
class ComponentRequirements
{
public:
    explicit ComponentRequirements(ComponentContainer& component_container) :
        m_component_container{component_container}
    {}

    ComponentRequirements(ComponentRequirements const&) = delete;
    ComponentRequirements& operator=(ComponentRequirements const&) = delete;

    template <typename T>
    bool getOrCreateComponent(core::sptr<T>& element)
    {
        if constexpr (requires { T::StaticTypeName; })
        {
            if (element == nullptr)
            {
                return getOrCreateComponentImp(element);
            }
        }

        return element != nullptr;
    }

    bool getOrCreateComponent(core::sptr<Component>& element,
                              core::str_view typeName);

private:
    template <typename T>
    bool getOrCreateComponentImp(core::sptr<T>& element)
    {
        element = m_component_container.getOrCreateComponent<T>();
        return element != nullptr;
    }

    template <typename T>
    bool getExistingComponentImp(core::sptr<T>& element)
    {
        m_component_container.getExistingComponent(element);
        return element != nullptr;
    }

    ComponentContainer& m_component_container;
};
}  // namespace haf::component

#endif
