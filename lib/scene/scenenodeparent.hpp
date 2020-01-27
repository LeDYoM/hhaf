#pragma once

#ifndef LIB_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define LIB_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
class SceneNode;
class Scene;

class SceneNodeParent
{
public:
    constexpr SceneNodeParent(
        rptr<SceneNode> parent, rptr<Scene> parent_scene) noexcept
        : parent_{std::move(parent)}, parent_scene_{std::move(parent_scene)} {}

    /// Virtual destructor.
    virtual ~SceneNodeParent() {}

    constexpr rptr<Scene> parentScene() noexcept
    {
        return parent_scene_;
    }

    constexpr const rptr<const Scene> parentScene() const noexcept
    {
        return parent_scene_;
    }

    template <typename SceneType>
    rptr<SceneType> parentSceneAs()
    {
        return dynamic_cast<SceneType *>(parentScene());
    }

    template <typename SceneType>
    const rptr<const SceneType> parentSceneAs() const
    {
        return dynamic_cast<const SceneType *>(parentScene());
    }

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
    rptr<T> snCast() noexcept { return dynamic_cast<T *const>(this); }

    template <typename T>
    const rptr<const T> snCast() const noexcept
    { 
        return dynamic_cast<const T *const>(this); 
    }

private:
    const rptr<SceneNode> parent_;
    rptr<Scene> parent_scene_;
    friend class Scene;
};

} // namespace lib::scene

#endif
