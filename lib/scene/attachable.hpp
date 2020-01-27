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
    /// Destructor
    virtual ~Attachable() {}

    /// Method called after the component is attached to a node.
    /// Override it to perform initialization
    virtual void onAttached() {}

    constexpr const rptr<const T> attachedNode() const noexcept { return attachedNode_; }
    constexpr const rptr<T> attachedNode() noexcept { return attachedNode_; }

    /// Shortcut method to cast to another scenenode type
    template <typename Y>
    inline rptr<Y> attachedNodeAs() noexcept
    { 
        return dynamic_cast<Y *>(attachedNode());
    }

protected:
    rptr<T> attachedNode_;
};

} // namespace lib::scene

#endif
