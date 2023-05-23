#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene_components/global_transformation_component.hpp>

#include <haf/include/profiler/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/properties/iproperty_state.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"

#include <haf/include/render/mesh_render_context.hpp>

#include <haf/include/core/geometry_math.hpp>

using namespace haf::math;
using namespace haf::core;

namespace haf::scene
{
void TransformationComponent::onAttached()
{
    addUpdater({this, &TransformationComponent::updateTransform}, &Position,
               &Scale, &Rotation);

    m_shared_connection.connect(
        getComponent<GlobalTransformationComponent>(), localMatrixChanged,
        core::make_function(
            getComponent<GlobalTransformationComponent>().get(),
            &GlobalTransformationComponent::localTransformationChanged));
}

void TransformationComponent::updateTransform() noexcept
{
    m_transform.setIdentity();
    m_transform.setColumn<3>(Position());
    m_transform.setDiagonal(Scale());
    //    m_transform.setRotation(Rotation(), 1.0F);
    localMatrixChanged(m_transform);
}

Matrix4x4 const& TransformationComponent::matrix() const noexcept
{
    return m_transform;
}

bool TransformationComponent::hasPendingMatrixUpdate() const noexcept
{
    return prop::ps_hasChanged(Position, Scale, Rotation);
}

}  // namespace haf::scene
