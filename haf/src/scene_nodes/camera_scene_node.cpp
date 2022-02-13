#include <haf/include/scene_nodes/camera_scene_node.hpp>
#include <backend_dev/include/icamera.hpp>

using namespace haf::types;

namespace haf::scene
{
struct CameraSceneNode::CameraSceneNodePrivate
{
    htps::rptr<backend::ICamera> icamera_{nullptr};
};

void CameraSceneNode::onCreated()
{
    view     = decltype(view)::value_type{{0, 0}, {1000, 1000}};
    viewPort = decltype(viewPort)::value_type{{0, 0}, {1, 1}};
}

void CameraSceneNode::update()
{
    if (view.readResetHasChanged())
    {
        p_->icamera_->setFarRect(view());
    }

    if (viewPort.readResetHasChanged())
    {
        p_->icamera_->setViewPort(viewPort());
    }
}

}  // namespace haf::scene
