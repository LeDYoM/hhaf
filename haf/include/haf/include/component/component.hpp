HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty_state.hpp>
#include <haf/include/component/component_updater.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{
class ComponentRequirements;

class Component : public ComponentUpdater
{
public:
    using pointer       = core::rptr<scene::SceneNode>;
    using const_pointer = core::rptr<scene::SceneNode const>;

    virtual constexpr const core::str_view staticTypeName() const noexcept = 0;

    Component(Component const&) = delete;
    Component& operator=(Component const&) = delete;
    Component(Component&&)                 = default;
    Component& operator=(Component&&) = default;

    void updateComponent();

    virtual ~Component();

    /**
     * @brief Get the attached node.
     * @return The pointer to const attached node.
     */
    const_pointer attachedNode() const noexcept;

    /**
     * @brief Get the attached node.
     * @return The pointer to the attached node.
     */
    pointer attachedNode() noexcept;

protected:
    Component();

private:
    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached();

    void setAttachedNode(pointer const attachedNode);
    virtual bool addRequirements(ComponentRequirements&);

    pointer attachedNode_{nullptr};
    friend class ComponentContainer;
};

}  // namespace haf::component

#endif
