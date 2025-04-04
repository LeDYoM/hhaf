#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/camera_component.hpp>

using namespace htps;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{htps::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    component::ComponentContainer{this},
    sys::SubSystemViewer{&isystemProvider()},
    Transformation(),
    global_transform_{}
{}

SceneNode::~SceneNode() = default;

void SceneNode::update()
{}

void SceneNode::postRender(SceneRenderContext& sceneRenderContext)
{
    //    HAF_PROFILE_SCENE_NODE_METHOD(prTime)

    auto const& transformable_parent{parent()};

    sceneRenderContext.currentTransformation = transformable_parent != nullptr
        ? transformable_parent->globalTransform()
        : Matrix4x4::Identity;

    bool localTransformationChanged{updateTransformIfNecessary()};
    /*
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
    */
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

void SceneNode::clearAll()
{
    clearSceneNodes();
}

Matrix4x4 const& SceneNode::globalTransform() const noexcept
{
    return global_transform_;
}

Matrix4x4 const& SceneNode::localTransform() const noexcept
{
    return matrix();
}

}  // namespace haf::scene
