#ifndef HAF_SCENE_TRANSFORMABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMABLE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene/transformable.hpp>

namespace haf::scene
{
class HAF_API TransformableSceneNode : public SceneNode, public Transformable
{
public:
    using SceneNode::prop;
    using Transformable::prop;

    using SceneNode::SceneNode;
};

}  // namespace haf::scene

#endif
