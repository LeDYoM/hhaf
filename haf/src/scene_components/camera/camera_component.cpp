#include <haf/include/scene_components/camera/camera_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"
#include <facil_math/include/geometry_math.hpp>
#include <facil_math/include/matrix4x4_functions.hpp>

using namespace haf::core;
using namespace haf::prop;
using namespace fmath;

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
               &Right, &Bottom, &Top, &Near, &Far, &FovY, &Aspect, &cameraMode);

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
    FovY       = 60.0F;
    Aspect     = 1.0F;
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
                fmath::frustum(Left(), Right(), Bottom(), Top(), Near(), Far());
            break;
        case CameraMode::Ortho:
            m_p->m_perspective_matrix =
                fmath::ortho(Left(), Right(), Bottom(), Top(), Near(), Far());
//            m_p->m_perspective_matrix = Matrix4x4::Identity;
            break;
        case CameraMode::Perspective:
            m_p->m_perspective_matrix =
                fmath::perspective(FovY(), Aspect(), Near(), Far());
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
    if (cameraMode() == CameraMode::Ortho)
    {
        m_p->m_view_matrix = Matrix4x4::Identity;
    }
    else
    {
        m_p->m_view_matrix = fmath::lookat(Position(), Center(), Up());
    }

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
