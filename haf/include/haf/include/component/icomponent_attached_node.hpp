#ifndef HAF_COMPONENT_ICOMPONENT_ATTACHED_NODE_INCLUDE_HPP
#define HAF_COMPONENT_ICOMPONENT_ATTACHED_NODE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{

class IComponentAttachedNode
{
public:

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~IComponentAttachedNode() = default;

    void setAttachedNodeNode(htps::rptr<scene::SceneNode> attachedNode) noexcept
    {
        attachedNode_ = std::move(attachedNode);
    }

protected:
    /**
     * @brief Get the attached node.
     * @return The pointer to const attached node.
     */
    constexpr htps::rptr<scene::SceneNode const> attachedNode() const noexcept
    {
        return attachedNode_;
    }

    /**
     * @brief Get the attached node.
     * @return The pointer to the attached node.
     */
    constexpr htps::rptr<scene::SceneNode> attachedNode() noexcept
    {
        return attachedNode_;
    }

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

private:
    htps::rptr<scene::SceneNode> attachedNode_{nullptr};
};

}  // namespace haf::component

#endif
