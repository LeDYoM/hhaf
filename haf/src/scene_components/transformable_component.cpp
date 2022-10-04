#include <haf/include/scene_components/transformable_component.hpp>
#include <haf/include/profiler/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"

using namespace htps;

namespace haf::scene
{
TransformableComponent::TransformableComponent() :
    Transformation(), global_transform_{}
{}

TransformableComponent::~TransformableComponent() = default;

Matrix4x4 const& TransformableComponent::globalTransform() const noexcept
{
    return global_transform_;
}

Matrix4x4 const& TransformableComponent::localTransform() const noexcept
{
    return matrix();
}

void TransformableComponent::setSceneRenderContext(
    SceneRenderContext& sceneRenderContext)
{
    m_sceneRenderContext = &sceneRenderContext;
}

void TransformableComponent::update()
{
    //    HAF_PROFILE_SCENE_NODE_METHOD(prTime)
    //    BaseClass::postRender(sceneRenderContext);

    auto const& parentTransformable{
        attachedNode()->parent()->componentOfType<TransformableComponent>()};

    m_sceneRenderContext->currentTransformation = parentTransformable
        ? parentTransformable->globalTransform()
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
            m_sceneRenderContext->parentTransformationChanged_;
    }

    if (localTransformationChanged)
    {
        global_transform_ =
            m_sceneRenderContext->currentTransformation * matrix();
    }

    m_sceneRenderContext->parentTransformationChanged_ =
        localTransformationChanged;
    m_sceneRenderContext = nullptr;
}

}  // namespace haf::scene
