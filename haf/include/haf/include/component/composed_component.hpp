HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_INCLUDE_HPP

#include <haf/include/component/icomponent.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{
template <typename T>
class ComposedComponent : public IComponent
{
private:
    using BaseClass = IComponent;

public:
    using composed_type = T;
    using composed_pointer = htps::rptr<T>;
    using const_composed_pointer = htps::rptr<T const>;

    /**
     * @brief Destroy the Attachable object
     */
    ~ComposedComponent() override = default;

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() override
    {
        BaseClass::onAttached();
    }

    const_composed_pointer composedComponent() const noexcept
    {
        return m_composed_component_pointer;
    }

    composed_pointer composedComponent() noexcept
    {
        return m_composed_component_pointer;
    }

private:
    void setComposedComponent(composed_pointer composedPointer)
    {
        m_composed_component_pointer = composedPointer;
    }

    composed_pointer m_composed_component_pointer{nullptr};
    friend class ComponentContainer;
};

}  // namespace haf::component

#endif
