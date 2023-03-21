#include <haf/include/scene_components/2.1/global_transformation_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/profiler/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/render/mesh_render_context.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"
#include "scene/scene_manager.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::math;

namespace haf::scene
{
void GlobalTransformationComponent::onAttached()
{
    BaseClass::onAttached();

    // Connect to receive the updates from a parent global transformation
    if (auto parentNode{attachedNode()->parent()}; parentNode != nullptr)
    {
        if (auto parentComponent{
                parentNode->componentOfType<GlobalTransformationComponent>()};
            parentComponent != nullptr)
        {
            m_receiver.connect(parentComponent,
                               parentComponent->m_globalTransformationChanged,
                               make_function(this,
                                             &GlobalTransformationComponent::
                                                 globalTransformationChanged));
        }
        else
        {
            DisplayLog::verbose(
                "No parent GlobalTransformationComponent found");
        }
    }
    else
    {
        DisplayLog::verbose("No parent found");
    }

    addUpdater({this, &GlobalTransformationComponent::updateMatrix},
               &m_localTransformation, &m_parentGlobalTransformation);
}

void GlobalTransformationComponent::localTransformationChanged(
    Matrix4x4 const& localTransform)
{
    m_localTransformation = localTransform;
}

void GlobalTransformationComponent::globalTransformationChanged(
    Matrix4x4 const& parentMatrix)
{
    m_parentGlobalTransformation = parentMatrix;
};

void GlobalTransformationComponent::updateMatrix()
{
    m_transform = m_parentGlobalTransformation() * m_localTransformation();

    if (auto meshRenderContext_{meshRenderContext()};
        !meshRenderContext_.empty())
    {
        meshRenderContext_->modelViewMatrix = m_transform;
    }

    m_globalTransformationChanged(m_transform);
}

bool GlobalTransformationComponent::hasPendingMatrixUpdate() const noexcept
{
    return prop::ps_hasChanged(m_parentGlobalTransformation,
                               m_localTransformation);
}

}  // namespace haf::scene
