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
    
}

void CameraSceneNode::update()
{
    if (near.hasChanged())
    {

    }
}

}  // namespace haf::scene
