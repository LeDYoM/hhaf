HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_WALKER_INCLUDE_HPP
#define HAF_SCENE_SCENE_WALKER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene
{
class SceneNode;
}  // namespace haf::scene

namespace haf::component
{
class Component;
}

namespace haf::scene
{
class SceneWalker final
{
public:
    void walk(SceneNode& node);
};

}  // namespace haf::scene

#endif
