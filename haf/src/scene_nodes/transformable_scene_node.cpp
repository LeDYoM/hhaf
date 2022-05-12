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
    global_transform_{},
    extra_transformations_{}
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

size_type TransformableSceneNode::addTransformation()
{
    extra_transformations_.emplace_back();
    return extra_transformations_.size();
}

size_type TransformableSceneNode::removeTransformation()
{
    LogAsserter::log_assert(
        !extra_transformations_.empty(),
        "There is only one transformation. Cannot remove one");
    extra_transformations_.pop_back();
    return extra_transformations_.size();
}

size_type TransformableSceneNode::numTransformations() const noexcept
{
    return extra_transformations_.size() + 1U;
}

bool TransformableSceneNode::updateLocalTransformationsIfNecessary() noexcept
{
    bool result{false};

    for (auto index{0U}; index < numTransformations(); ++index)
    {
        result |= getTransformation(index).updateTransformIfNecessary();
    }

    // Result contains if any of the sub local transformations has changed.
    if (result)
    {
        local_transform_ = Matrix4x4::Identity;
        for (auto index{0U}; index < numTransformations(); ++index)
        {
            local_transform_ *= getTransformation(index).matrix();
        }
    }

    return result;
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

Transformation& TransformableSceneNode::getTransformation(
    size_type const index) noexcept
{
    LogAsserter::log_assert(index < numTransformations());

    return (index == 0U || index >= numTransformations())
        ? static_cast<Transformation&>(*this)
        : extra_transformations_[index - 1U];
}

void TransformableSceneNode::updateGlobalTransformation(
    Matrix4x4 const& currentGlobalTransformation) noexcept
{
    global_transform_ = currentGlobalTransformation * local_transform_;
}

void TransformableSceneNode::reserveExtraTransformations(
    size_type const minimum_size)
{
    extra_transformations_.reserve(minimum_size);
}

}  // namespace haf::scene
