#pragma once

#ifndef LIB_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define LIB_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
class SceneNode;
class Scene;

/// Class encapsulating the functionallity related to the parent and
/// ancestors management.
class SceneNodeParent
{
public:
    /// Constructor.
    /// @param[in] parent       The parent of this node.
    constexpr SceneNodeParent(
        rptr<SceneNode> parent) noexcept : parent_{std::move(parent)} {}

    /// Virtual destructor.
    virtual ~SceneNodeParent() {}

    constexpr rptr<SceneNode> parent() noexcept { return parent_; }
    constexpr const rptr<const SceneNode> parent() const noexcept { return parent_; }

    template <typename SceneNodeType>
    rptr<SceneNodeType> parentAs() noexcept
    {
        return dynamic_cast<SceneNodeType *>(parent());
    }

    template <typename SceneNodeType>
    const rptr<const SceneNodeType> parentAs() const noexcept
    {
        return dynamic_cast<const SceneNodeType *>(parent());
    }

    template <typename T>
    rptr<T> snCast() noexcept { return dynamic_cast<T *>(this); }

    template <typename T>
    const rptr<const T> snCast() const noexcept
    {
        return dynamic_cast<const T *const>(this);
    }

    template <typename T = SceneNode>
    constexpr rptr<T> ancestor() noexcept
    {
        rptr<SceneNode> _parent{parent()};
        if (_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            auto parent_as_type{_parent->snCast<T>()};
            return parent_as_type == nullptr ? _parent->ancestor<T>() : parent_as_type;
        }
    }

    template <typename T = SceneNode>
    constexpr const rptr<const T> ancestor() const noexcept
    {
        rptr<const SceneNode> _parent{parent()};
        if (_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            auto parent_as_type{_parent->snCast<T>()};
            return parent_as_type == nullptr ? _parent->ancestor<T>() : parent_as_type;
        }
    }

private:
    const rptr<SceneNode> parent_;
};

} // namespace lib::scene

#endif
