#include <haf/include/scene_nodes/transformable_scene_node.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
TransformableSceneNode::TransformableSceneNode(htps::rptr<SceneNode> parent,
                                               htps::str name) :
    SceneNode{htps::move(parent), htps::move(name)},
    Transformation(),
    local_transform_{},
    global_transform_{}
{}

TransformableSceneNode::~TransformableSceneNode() = default;

Matrix4x4 const& TransformableSceneNode::globalTransform() const noexcept
{
    return global_transform_;
}

Matrix4x4 const& TransformableSceneNode::localTransform() const noexcept
{
    return local_transform_;
}

bool TransformableSceneNode::updateLocalTransformationsIfNecessary() noexcept
{
    if (updateTransformIfNecessary())
    {
        local_transform_ = matrix();
        return true;
    }

    return false;
}

void TransformableSceneNode::postUpdate(SceneRenderContext& sceneRenderContext)
{
    BaseSceneNode::postUpdate(sceneRenderContext);

    sceneRenderContext.currentTransformation =
        parentAs<TransformableSceneNode>()
        ? parentAs<TransformableSceneNode>()->globalTransform()
        : Matrix4x4::Identity;

    bool const localTransformationChanged =
        updateLocalTransformationsIfNecessary() ||
        sceneRenderContext.parentTransformationChanged_;

    if (localTransformationChanged)
    {
        updateGlobalTransformation(sceneRenderContext.currentTransformation);
    }
    sceneRenderContext.parentTransformationChanged_ =
        localTransformationChanged;
}

void TransformableSceneNode::updateGlobalTransformation(
    Matrix4x4 const& currentGlobalTransformation) noexcept
{
    global_transform_ = currentGlobalTransformation * local_transform_;
}

}  // namespace haf::scene
