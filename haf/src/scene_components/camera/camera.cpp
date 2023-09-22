#include <haf/include/scene_components/camera/camera.hpp>
#include <haf/include/scene/scene_node.hpp>

namespace haf::scene
{
bool CameraBuilder::addDebugMovableCamera(SceneNode& node)
{
    bool isOk{true};
    isOk &= (node.componentContainer().attachComponent("MoveCameraComponent") != nullptr);
    isOk &= (node.componentContainer().attachComponent("DebugCameraComponent") != nullptr);
    return isOk;
}
}  // namespace haf::scene