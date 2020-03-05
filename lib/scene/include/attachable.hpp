#pragma once

#ifndef LIB_SCENE_ATTACHABLE_INCLUDE_HPP
#define LIB_SCENE_ATTACHABLE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
template <typename T>
class Attachable
{
public:
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
     * @return const rptr<const T> The const attached node.
     */
    constexpr const rptr<const T> attachedNode() const noexcept { return attachedNode_; }

    /**
     * @brief Get the attached node.
     * @return const rptr<const T> The attached node.
     */
    constexpr const rptr<T> attachedNode() noexcept { return attachedNode_; }

    /**
     * @brief Shortcut method to get the attached node converted to a type.
     * 
     * @tparam Y Dest type to convert
     * @return rptr<Y> containing the attached node or nullptr if no conversion
     *  was possible.
     */
    template <typename Y>
    rptr<Y> attachedNodeAs() noexcept
    {
        return dynamic_cast<Y *>(attachedNode());
    }

public:
    rptr<T> attachedNode_;
};

} // namespace lib::scene

#endif
