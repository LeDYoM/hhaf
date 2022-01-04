#ifndef HAF_COMPONENT_ICOMPONENT_ATTACHED_NODE_INCLUDE_HPP
#define HAF_COMPONENT_ICOMPONENT_ATTACHED_NODE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf::component
{
template <typename T>
class IComponentAttachedNode
{
public:
    using type = T;
    using pointer = htps::rptr<type>;
    using const_pointer = htps::rptr<type const>;

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~IComponentAttachedNode() = default;

    void setAttachedNodeNode(pointer const attachedNode) noexcept
    {
        attachedNode_ = attachedNode;
    }

protected:
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
    constexpr pointer attachedNode() noexcept
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
    pointer attachedNode_{nullptr};
};

}  // namespace haf::component

#endif
