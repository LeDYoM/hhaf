#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"
#include <haf/include/core/geometry_math.hpp>

using namespace haf::core;

namespace haf::scene
{
void CameraComponent::onAttached()
{
    addUpdater({this, &CameraComponent::cameraDataUpdated}, &Left, &Right,
               &Bottom, &Top, &Near, &Far, &cameraMode, &Position, &Center,
               &Up);
    Left            = -1.0F;
    Right           = 1.0F;
    Bottom          = -1.0F;
    Top             = 1.0F;
    Near            = 0.0F;
    Far             = 5.0F;
    cameraMode      = CameraMode::Perspective;
    Position        = vector3df{0.0F, 0.0F, 1.0F};
    Center          = vector3df{0.0F, 0.0F, 0.0F};
    Up              = vector3df{0.0F, 1.0F, 0.0F};

    //    setPerspective(50, 1);
}

void CameraComponent::setPerspective(core::f32 const fovy,
                                     core::f32 const aspect)
{
    f32 const fH{std::tan((fovy * 0.5F) / 180 * math::PiConstant<f32>) *
                 Near()};
    //    fH = std::tan(fovy / 360 * pi) * Near();
    f32 fW{fH * aspect};

    Left   = -fW;
    Right  = fW;
    Bottom = -fH;
    Top    = fH;
}

void CameraComponent::cameraDataUpdated()
{
    switch (cameraMode())
    {
        case CameraMode::Frustum:
            [[fallthrough]];
        case CameraMode::Ortho:
            m_perspective_matrix =
                (cameraMode() == CameraMode::Ortho ? math::ortho
                                                   : math::frustum)(
                    Left(), Right(), Bottom(), Top(), Near(), Far());
            break;
        case CameraMode::Perspective:
            m_perspective_matrix =
                math::perspective(60, 800.0F / 600.0F, 0.01F, 10.0F);
            break;
        default:
            LogAsserter::log_assert(true, "Invalid CameraMode value");
            break;
    }

    m_perspective_matrix =
        m_perspective_matrix * math::lookat(Position(), Center(), Up());

    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneRenderContext()
        .setCameraMatrix(m_perspective_matrix);

    cameraUpdated();
}

}  // namespace haf::scene
