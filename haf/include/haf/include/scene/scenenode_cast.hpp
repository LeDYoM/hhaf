HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENENODE_CAST_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_CAST_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/cast.hpp>

namespace haf::scene
{
class SceneNode;

template <typename T>
htps::rptr<T> sceneNodeCast(htps::rptr<SceneNode> const scene_node) noexcept
{
    return htps::d_cast<htps::rptr<T>>(scene_node);
}

template <typename T>
htps::rptr<const T> sceneNodeCast(
    htps::rptr<SceneNode const> const scene_node) noexcept
{
    return htps::d_cast<T const*>(scene_node);
}

template <typename T>
htps::sptr<T> sceneNodeCast(htps::sptr<SceneNode> scene_node) noexcept
{
    return htps::dynamic_pointer_cast<T>(scene_node);
}

template <typename T>
const htps::sptr<const T> sceneNodeCast(
    htps::sptr<SceneNode const> const scene_node) noexcept
{
    return htps::dynamic_pointer_cast<const T>(scene_node);
}

}  // namespace haf::scene

#endif
