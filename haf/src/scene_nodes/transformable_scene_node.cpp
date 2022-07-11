#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/profiler/code_profiler.hpp>
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

void TransformableSceneNode::postRender(SceneRenderContext& sceneRenderContext)
{
    HAF_PROFILE_SCENE_NODE_METHOD(testing, buh)
    BaseSceneNode::postRender(sceneRenderContext);

    sceneRenderContext.currentTransformation =
        parentAs<TransformableSceneNode>()
        ? parentAs<TransformableSceneNode>()->globalTransform()
        : Matrix4x4::Identity;

    bool localTransformationChanged{updateTransformIfNecessary()};
    if (localTransformationChanged)
    {
        local_transform_ = matrix();
    }
    else
    {
        localTransformationChanged =
            sceneRenderContext.parentTransformationChanged_;
    }

    if (localTransformationChanged)
    {
        global_transform_ =
            sceneRenderContext.currentTransformation * local_transform_;
    }

    sceneRenderContext.parentTransformationChanged_ =
        localTransformationChanged;
}

}  // namespace haf::scene
