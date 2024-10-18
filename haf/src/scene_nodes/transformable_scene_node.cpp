#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/profiler/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"

using namespace htps;

namespace haf::scene
{
TransformableSceneNode::TransformableSceneNode(htps::rptr<SceneNode> parent,
                                               htps::str name) :
    SceneNode{htps::move(parent), htps::move(name)},
    Transformation(),
    global_transform_{}
{}

TransformableSceneNode::~TransformableSceneNode() = default;

Matrix4x4 const& TransformableSceneNode::globalTransform() const noexcept
{
    return global_transform_;
}

Matrix4x4 const& TransformableSceneNode::localTransform() const noexcept
{
    return matrix();
}

void TransformableSceneNode::postRender(SceneRenderContext& sceneRenderContext)
{
    HAF_PROFILE_SCENE_NODE_METHOD(prTime)
    BaseSceneNode::postRender(sceneRenderContext);

    auto const& transformable_parent{parentAs<TransformableSceneNode>()};

    if (transformable_parent != nullptr)
    {
        sceneRenderContext.currentTransformation =
            transformable_parent != nullptr
            ? transformable_parent->globalTransform()
            : Matrix4x4::Identity;
    }

    bool localTransformationChanged{updateTransformIfNecessary()};

    HAF_DECLARE_DEBUG_VARIABLE(matrix_updater_counter)
    if (HAF_DEBUG_VARIABLE_NAME(matrix_updater_counter) < 0)
    {
        subSystem<debug::IDebugVariables>()->getVariable(
            HAF_DEBUG_VARIABLE_NAME(matrix_updater_counter), "muc");
    }
    else
    {
        debug::DebugVariable value{0};

        subSystem<debug::IDebugVariables>()->getVariableValue(
            HAF_DEBUG_VARIABLE_NAME(matrix_updater_counter), value);

        if (value.value() < 5)
            subSystem<debug::IDebugVariables>()->incrementVariable(
                HAF_DEBUG_VARIABLE_NAME(matrix_updater_counter), 1);
    }

    if (!localTransformationChanged)
    {
        localTransformationChanged =
            sceneRenderContext.parentTransformationChanged_;
    }

    if (localTransformationChanged)
    {
        global_transform_ = sceneRenderContext.currentTransformation * matrix();
    }

    sceneRenderContext.parentTransformationChanged_ =
        localTransformationChanged;
}

}  // namespace haf::scene
