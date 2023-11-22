#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <facil_math/include/geometry_math.hpp>
#include <haf/include/scene_components/global_transformation_component.hpp>

using namespace haf::math;
using namespace haf::core;

namespace haf::scene
{
struct TransformationComponent::ComponentsRequired
{
    sptr<GlobalTransformationComponent> m_globalTransformationComponent;
};

struct TransformationComponent::PrivateComponentData
{
    Matrix4x4 m_transform;

    rptr<TransformationComponent> parentTransformationComponent(
        rptr<SceneNode> attachedNode) const noexcept
    {
        return attachedNode->ancestor<TransformationComponent>();
    }
};

TransformationComponent::TransformationComponent() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

TransformationComponent::~TransformationComponent() = default;

bool TransformationComponent::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_globalTransformationComponent);
    return isOk;
}

void TransformationComponent::onAttached()
{
    addUpdater({this, &TransformationComponent::updateLocalTransformation},
               &Position, &Scale, &Rotation);

    localMatrixChanged.connect(make_function(
        m_components->m_globalTransformationComponent.get(),
        &GlobalTransformationComponent::localTransformationChanged));
}

void TransformationComponent::updateLocalTransformation() noexcept
{
    m_p->m_transform.setIdentity();
    m_p->m_transform.setColumn<3>(Position());
    m_p->m_transform.setDiagonal(Scale());
    //    m_p->m_transform.setRotation(Rotation(), 1.0F);
    localMatrixChanged(m_p->m_transform);
}

Matrix4x4 const& TransformationComponent::matrix() const noexcept
{
    return m_p->m_transform;
}

bool TransformationComponent::hasPendingMatrixUpdate() const noexcept
{
    return prop::ps_hasChanged(Position, Scale, Rotation);
}

}  // namespace haf::scene
