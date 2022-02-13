#ifndef HAF_SCENE_NODES_CAMERA_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_NODES_CAMERA_SCENENODE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/types/basic_types.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/types/scene_types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
class HAF_API CameraSceneNode : public SceneNode
{
    using SceneNodeBaseClass = SceneNode;

public:
    using SceneNodeBaseClass::prop;
    using SceneNodeBaseClass::SceneNodeBaseClass;

    htps::PropertyState<SceneBox> view;
    htps::PropertyState<SceneQuad> viewPort;

    void onCreated() override;
    void update() override;

private:
    struct CameraSceneNodePrivate;
    htps::PImplPointer<CameraSceneNodePrivate> p_;
};
}  // namespace haf::scene

#endif
