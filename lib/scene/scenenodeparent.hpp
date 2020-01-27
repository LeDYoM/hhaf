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
    constexpr SceneNodeParent(rptr<SceneNode> parent, rptr<Scene> parent_scene)
        : parent_{parent},
          parent_scene_{parent_scene}
    {
    }

    /// Virtual destructor.
    virtual ~SceneNodeParent() {}

    rptr<Scene> parentScene() noexcept
    {
        return parent_scene_;
    }

    const rptr<Scene> parentScene() const noexcept
    {
        return parent_scene_;
    }

    template <typename SceneType>
    SceneType *const parentSceneAs()
    {
        return dynamic_cast<SceneType *>(parentScene());
    }

    template <typename SceneType>
    const SceneType *const parentSceneAs() const
    {
        return dynamic_cast<const SceneType *>(parentScene());
    }

    SceneNode *parent() noexcept { return parent_; }
    const SceneNode *parent() const noexcept { return parent_; }

    template <typename SceneNodeType>
    SceneNodeType *parentAs()
    {
        return dynamic_cast<SceneNodeType *>(parent());
    }

    template <typename SceneNodeType>
    const SceneNodeType *parentAs() const
    {
        return dynamic_cast<const SceneNodeType *>(parent());
    }

    template <typename T>
    constexpr T *const snCast() { return dynamic_cast<T *const>(this); }

    template <typename T>
    constexpr const T *const snCast() const { return dynamic_cast<const T *const>(this); }

private:
    rptr<SceneNode> parent_;
    rptr<Scene> parent_scene_;
    friend class Scene;
};

} // namespace lib::scene

#endif
