HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_MOVE_CAMERA_INCLUDE_HPP
#define HAF_SCENE_MOVE_CAMERA_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::scene
{
class CameraBuilder
{
public:
    bool addDebugMovableCamera(SceneNode& node);
};
}  // namespace haf::scene

#endif
