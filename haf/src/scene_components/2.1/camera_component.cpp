#include <haf/include/scene_components/2.1/camera_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/resources/shader.hpp>

#include <hlog/include/hlog.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"
#include "resources/resource_manager.hpp"
#include <haf/include/scene/color.hpp>
#include <hogl/include/render_system_functions.hpp>
#include <haf/include/core/geometry_math.hpp>

using namespace haf::core;

namespace haf::scene
{
void CameraComponent::onAttached()
{
    addUpdater({this, &CameraComponent::cameraDataUpdated}, &Left, &Right,
               &Bottom, &Top, &Near, &Far, &cameraMode, &Position, &Center,
               &Up);
    //    addUpdater({this, &CameraComponent::cameraDataUpdated});
    addUpdater({this, &CameraComponent::clearBackground});
    Left            = -1.0F;
    Right           = 1.0F;
    Bottom          = -1.0F;
    Top             = 1.0F;
    Near            = 0.0F;
    Far             = 5.0F;
    cameraMode      = CameraMode::Perspective;
    backgroundColor = colors::DarkGreen;
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
            m_perspective_matrix = math::perspective(60, 800.0F / 600.0F, 0.01F, 10.0F);
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

    [[maybe_unused]] auto const count{
        sys::getSystem<sys::ResourceManager>(attachedNode())
            .shaderManager()
            .setUniformForAll("haf_camera_projection", m_perspective_matrix)};

    DisplayLog::debug(
        StaticTypeName, ": Camera view updated. New values:\nPosition: {",
        Position().x, ",", Position().y, ",", Position().z, "}\nCenter: {",
        Center().x, ",", Center().y, ",", Center().z, "}\nUp: {", Up().x, ",",
        Up().y, ",", Up().z, "}");

    DisplayLog::debug(
        StaticTypeName, ": Mode: ",
        cameraMode() == CameraMode::Ortho
            ? "Ortho"
            : (cameraMode() == CameraMode::Frustum ? "Frustum"
                                                   : "Perspective"));

    DisplayLog::debug(StaticTypeName,
                      ": Camera perspectve updated. New values:\n: Left Right "
                      "Bottom Top Near Far\n",
                      Left(), ",", Right(), ",", Bottom(), ",", Top(), ",",
                      Near(), ",", Far());

    DisplayLog::debug(StaticTypeName, ": Camera updated in ", count,
                      " shader(s)");
}

void CameraComponent::clearBackground()
{
    ogl::clearBackgroundColor(backgroundColor());
    ogl::clearDepthBuffer();
}

}  // namespace haf::scene

//    static core::f32 mz{1.0F};
//    mz += 0.001F;
//    math::Matrix4x4 matrix;
// core::f32 aspect = 800.0F / 600.0F;
//    matrix.setDiagonal(core::vector3df{2.0F, 2.0F, 1.0F});
//    matrix = math::lookat(core::vector3df{0.0F, 0.0F, -0.15F},
//    core::vector3df{mz, 0.0F, mz},
//                 core::vector3df{0.0F, 1.0F, 0.0F});
//        matrix = math::ortho(-2.0F,2.0F, -2.0F, 2.0F, -5.0F, 10.0F);
//    matrix = math::frustum(-1.0F,1.0F, -1.0F, 1.0F, 1.0F, 10.0F);
//    matrix = math::perspective(50.0F, aspect, 0.1F, 1000.0F);

//    m_perspective_matrix =
//        math::frustum(-1.0F, 1.0F, -1.0F, 1.0F, 1.0F, 100.0F);
//    static core::vector3df position = core::vector3df{0.0F, 0.0F, 0.0F};
//    position.z -= 0.0001F;

//    math::Matrix4x4 look_at_matrix;
