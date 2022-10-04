HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_ICOMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_ICOMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{

class IComponent
{
public:
    using pointer       = htps::rptr<scene::SceneNode>;
    using const_pointer = htps::rptr<scene::SceneNode const>;

    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() {}

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~IComponent() = default;

    IComponent(IComponent const&) = delete;
    IComponent& operator=(IComponent const&) = delete;

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() {}

    /**
     * @brief Get the attached node.
     * @return The pointer to const attached node.
     */
    constexpr const_pointer attachedNode() const noexcept
    {
        return attachedNode_;
    }

    /**
     * @brief Get the attached node.
     * @return The pointer to the attached node.
     */
    constexpr pointer attachedNode() noexcept { return attachedNode_; }

    /**
     * @brief Shortcut method to get the attached node converted to a type.
     *
     * @tparam Y Dest type to convert
     * @return htps::rptr<Y> containing the attached node or nullptr if no
     * conversion was possible.
     */
    template <typename Y>
    htps::rptr<Y> attachedNodeAs() noexcept
    {
        return dynamic_cast<Y*>(attachedNode());
    }

    /**
     * @brief Shortcut method to get the attached node converted to a type.
     * Const version
     *
     * @tparam Y Dest type to convert
     * @return htps::rptr<Y> containing the attached node or nullptr if no
     * conversion was possible.
     */
    template <typename Y>
    htps::rptr<Y const> attachedNodeAs() const noexcept
    {
        return dynamic_cast<Y const*>(attachedNode());
    }

protected:
    IComponent() noexcept = default;

private:
    void setAttachedNode(pointer const attachedNode) noexcept
    {
        attachedNode_ = attachedNode;
        onAttached();
    }

    pointer attachedNode_{nullptr};
    friend class ComponentContainer;
};

}  // namespace haf::component

#endif
