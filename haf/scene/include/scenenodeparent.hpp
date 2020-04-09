#pragma once

#ifndef HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::scene
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
        mtps::rptr<SceneNode> parent) noexcept : parent_{std::move(parent)} {}

    /// Virtual destructor.
    virtual ~SceneNodeParent() {}

    constexpr mtps::rptr<SceneNode> parent() noexcept { return parent_; }
    constexpr const mtps::rptr<const SceneNode> parent() const noexcept { return parent_; }

    template <typename SceneNodeType>
    mtps::rptr<SceneNodeType> parentAs() noexcept
    {
        return dynamic_cast<SceneNodeType *>(parent());
    }

    template <typename SceneNodeType>
    const mtps::rptr<const SceneNodeType> parentAs() const noexcept
    {
        return dynamic_cast<const SceneNodeType *>(parent());
    }

    template <typename T>
    mtps::rptr<T> snCast() noexcept { return dynamic_cast<T *>(this); }

    template <typename T>
    const mtps::rptr<const T> snCast() const noexcept
    {
        return dynamic_cast<const T *const>(this);
    }

    template <typename T = SceneNode>
    constexpr mtps::rptr<T> ancestor() noexcept
    {
        mtps::rptr<SceneNode> _parent{parent()};
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
    constexpr const mtps::rptr<const T> ancestor() const noexcept
    {
        mtps::rptr<const SceneNode> _parent{parent()};
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
    const mtps::rptr<SceneNode> parent_;
};

} // namespace haf::scene

#endif
