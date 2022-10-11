HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_REQUIREMENTS_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_REQUIREMENTS_INCLUDE_HPP

#include <htypes/include/types.hpp>
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
    htps::sptr<T> component()
    {
        return m_component_container.component<T>();
    }

    template <typename T>
    htps::sptr<T> componentOfType() const
    {
        return m_component_container.componentOfType<T>();
    }

    template <typename T>
    void componentOfType(htps::sptr<T>& element) const
    {
        element = m_component_container.componentOfType<T>();
    }

    template <typename T>
    void component(htps::sptr<T>& element)
    {
        m_component_container.component(element);
    }

private:
    ComponentContainer& m_component_container;
};
}  // namespace haf::component

#endif
