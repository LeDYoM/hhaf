HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_UPDATE_NODE_INCLUDE_HPP
#define HAF_SCENE_SCENE_UPDATE_NODE_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::scene
{
enum class SceneUpdateTime : core::u32
{
    Controller = 0U,
    BeginFrame = 1U,
    EndFrame   = 2U,
    Render     = 3U,
    Count      = 4U
};
}

#endif
