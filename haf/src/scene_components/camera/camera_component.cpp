#include <haf/include/scene_components/camera/camera_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene_components/scene_render_properties_component.hpp>
#include <haf/include/resources/shader.hpp>

#include <haf/include/log/assert.hpp>

using namespace haf::core;
using namespace haf::prop;
using namespace haf::math;

namespace haf::scene
{
struct CameraComponent::ComponentsRequired
{
    sptr<haf::scene::SceneRenderPropertiesComponent> m_scene_render_properties;
};

struct CameraComponent::PrivateComponentData
{
    Matrix4x4 m_perspective_matrix;
    Matrix4x4 m_view_matrix;
    vector<res::Shader> m_shaders_with_camera_projection;
    struct CameraComponentsUpdatedStruct
    {};
    PropertyState<CameraComponentsUpdatedStruct> cameraComponentsUpdated;
};

CameraComponent::CameraComponent() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

CameraComponent::~CameraComponent() = default;

bool CameraComponent::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_scene_render_properties);
    return isOk;
}

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
            LOG_ASSERT(false, "Invalid CameraMode value");
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
    m_components->m_scene_render_properties->setViewMatrix(
        m_p->m_perspective_matrix * m_p->m_view_matrix);
    cameraUpdated();
}

}  // namespace haf::scene
