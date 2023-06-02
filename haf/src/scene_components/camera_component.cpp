#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"
#include <haf/include/core/geometry_math.hpp>

using namespace haf::core;
using namespace haf::prop;
using namespace haf::math;

namespace haf::scene
{
struct CameraComponent::PrivateComponentData
{
    Matrix4x4 m_perspective_matrix;
    Matrix4x4 m_view_matrix;
    vector<res::Shader> m_shaders_with_camera_projection;
    struct CameraComponentsUpdatedStruct
    {};
    PropertyState<CameraComponentsUpdatedStruct> cameraComponentsUpdated;
};

CameraComponent::CameraComponent() : m_p{make_pimplp<PrivateComponentData>()}
{}

CameraComponent::~CameraComponent() = default;

void CameraComponent::onAttached()
{
    addUpdater({this, &CameraComponent::cameraDataPerspectiveUpdated}, &Left,
               &Right, &Bottom, &Top, &Near, &Far, &cameraMode);

    addUpdater({this, &CameraComponent::cameraDataViewUpdated}, &Position,
               &Center, &Up);

    addUpdater({this, &CameraComponent::performCameraUpdate},
               &m_p->cameraComponentsUpdated);

    Left       = -0.05F;
    Right      = 0.05F;
    Bottom     = -0.05F;
    Top        = 0.05F;
    Near       = 0.01F;
    Far        = 1.0F;
    cameraMode = CameraMode::Frustum;
    Position   = vector3df{0.0F, 0.0F, 0.4F};
    Center     = vector3df{0.0F, 0.0F, 0.0F};
    Up         = vector3df{0.0F, 1.0F, 0.0F};
}

void CameraComponent::cameraDataPerspectiveUpdated()
{
    switch (cameraMode())
    {
        case CameraMode::None:
            m_p->m_perspective_matrix.setIdentity();
            break;
        case CameraMode::Frustum:
            m_p->m_perspective_matrix =
                math::frustum(Left(), Right(), Bottom(), Top(), Near(), Far());
            break;
        case CameraMode::Ortho:
            m_p->m_perspective_matrix =
                math::ortho(Left(), Right(), Bottom(), Top(), Near(), Far());
            break;
        case CameraMode::Perspective:
            m_p->m_perspective_matrix =
                math::perspective(60, 800.0F / 600.0F, 0.01F, 10.0F);
            break;
        default:
            LogAsserter::log_assert(true, "Invalid CameraMode value");
            break;
    }

    m_p->cameraComponentsUpdated.setChanged();
    cameraPerspectiveUpdated();
}

void CameraComponent::cameraDataViewUpdated()
{
    m_p->m_view_matrix = math::lookat(Position(), Center(), Up());

    m_p->cameraComponentsUpdated.setChanged();
    cameraViewUpdated();
}

void CameraComponent::performCameraUpdate()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneRenderContext()
        .setCameraMatrix(m_p->m_perspective_matrix * m_p->m_view_matrix);

    cameraUpdated();
}

}  // namespace haf::scene
