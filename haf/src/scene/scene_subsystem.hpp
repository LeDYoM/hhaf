HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_SCENE_SUBSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "haf_private.hpp"
#include <haf/include/scene/scene_node.hpp>

namespace haf::scene
{
template <typename T>
class HAF_PRIVATE SceneSubsystem
{
public:
    constexpr void init()
    {
        T::init();
    }

    constexpr void finish()
    {
        T::finish();
    }

    constexpr void initPass()
    {
        T::initPass();
    }

    constexpr void finishPass()
    {
        T::finishPass();
    }

    constexpr void updateNodeDownTree(SceneNode& node)
    {
        T::update();

        for (auto& group : node.sceneNodes())
        {
            updateNodeDownTree(*group);
        }

        T::updateNodeDownTree(node);
    }
};

}  // namespace haf::scene

#endif
