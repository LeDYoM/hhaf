#ifndef HAF_SYS_ATTACHABLE_INCLUDE_HPP
#define HAF_SYS_ATTACHABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::utils
{
template <typename T>
class Attachable
{
public:
    /**
     * @brief Type that composes this attachable.
     */
    using AttachedNodeType = T;

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~Attachable() {}

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() {}

    /**
     * @brief Get the attached node.
     * @return const mtps::rptr<const T> The const attached node.
     */
    constexpr const mtps::rptr<const T> attachedNode() const noexcept
    {
        return attachedNode_;
    }

    /**
     * @brief Get the attached node.
     * @return const mtps::rptr<const T> The attached node.
     */
    constexpr const mtps::rptr<T> attachedNode() noexcept
    {
        return attachedNode_;
    }

    /**
     * @brief Shortcut method to get the attached node converted to a type.
     *
     * @tparam Y Dest type to convert
     * @return mtps::rptr<Y> containing the attached node or nullptr if no
     * conversion was possible.
     */
    template <typename Y>
    mtps::rptr<Y> attachedNodeAs() noexcept
    {
        return dynamic_cast<Y*>(attachedNode());
    }

public:
    mtps::rptr<T> attachedNode_;
};

}  // namespace haf::utils

#endif
