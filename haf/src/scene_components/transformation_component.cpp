#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <facil_math/include/geometry_math.hpp>

using namespace fmath;
using namespace haf::core;

namespace haf::scene
{
struct TransformationComponent::ComponentsRequired
{};

struct TransformationComponent::PrivateComponentData
{
    Matrix4x4 m_transform;
    Matrix4x4 m_globalTransform;
    bool m_transformation_updated{true};

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

void TransformationComponent::onAttached()
{
    addUpdater({this, &TransformationComponent::updateLocalTransformation},
               &Position, &Scale, &Rotation);

    addUpdater(
        {this, &TransformationComponent::pollParentGlobalTransformation});

    addUpdater(
        {this,
         &TransformationComponent::updateMyGlobalTransformationIfNecessary});
}

void TransformationComponent::updateLocalTransformation() noexcept
{
    m_p->m_transform.setIdentity();
    m_p->m_transform.setColumn<3>(Position());
    m_p->m_transform.setDiagonal(Scale());
    //    m_p->m_transform.setRotation(Rotation(), 1.0F);
    m_p->m_transformation_updated = true;
    localMatrixChanged(m_p->m_transform);
}

void TransformationComponent::pollParentGlobalTransformation() noexcept
{
    if (auto const& parentTransformation{
            m_p->parentTransformationComponent(attachedNode())};
        parentTransformation != nullptr)
    {
        if (parentTransformation->transformationUpdated())
        {
            m_p->m_transformation_updated = true;
        }
    }
}

void TransformationComponent::updateMyGlobalTransformationIfNecessary() noexcept
{
    if (m_p->m_transformation_updated)
    {
        if (auto const& parentTransformation{
                m_p->parentTransformationComponent(attachedNode())};
            parentTransformation != nullptr)
        {

            m_p->m_globalTransform = m_p->m_globalTransform =
                parentTransformation->getGlobalTransformation() *
                m_p->m_transform;
        }
    }
}

bool TransformationComponent::transformationUpdated() const noexcept
{
    return m_p->m_transformation_updated;
}

Matrix4x4 const& TransformationComponent::matrix() const noexcept
{
    return m_p->m_transform;
}

Matrix4x4 TransformationComponent::getGlobalTransformation()
{
    return m_p->m_globalTransform;
}

bool TransformationComponent::hasPendingMatrixUpdate() const noexcept
{
    return prop::ps_hasChanged(Position, Scale, Rotation);
}

}  // namespace haf::scene
