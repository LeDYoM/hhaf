#pragma once

#ifndef HAF_SCENE_SCENENODE_CAST_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_CAST_INCLUDE_HPP

#include <mtypes/include/types.hpp>


namespace haf::scene
{
    class SceneNode;

    template <typename T>
    mtps::rptr<T> sceneNodeCast(mtps::rptr<SceneNode> const scene_node) noexcept
    {
        return dynamic_cast<T*>(scene_node);
    }

    template <typename T>
    const mtps::rptr<const T> sceneNodeCast(mtps::rptr<SceneNode const> const scene_node) noexcept
    {
        return dynamic_cast<const T* const>(scene_node);
    }
};

}  // namespace haf::scene

#endif
