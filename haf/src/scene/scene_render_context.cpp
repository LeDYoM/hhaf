#include <haf/include/scene/scene_render_context.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::scene
{
SceneRenderContext::SceneRenderContext()  = default;
SceneRenderContext::~SceneRenderContext() = default;

void SceneRenderContext::init()
{
    m_backgroundColor = colors::DarkGreen;
}

void SceneRenderContext::setNowFrame(time::TimePoint time_point)
{
    m_nowFrame = core::move(time_point);
}

void SceneRenderContext::setBackgroundColor(
    core::vector4df const& backgroundColor) noexcept
{
    m_backgroundColor = backgroundColor;
}

void SceneRenderContext::setCameraMatrix(math::Matrix4x4 const& camera_matrix)
{
    m_cameraMatrix = camera_matrix;
}

void SceneRenderContext::setCurrentModelViewMatrix(
    math::Matrix4x4 const& matrix) noexcept
{
    m_currentModeViewMatrix = matrix;
}

void SceneRenderContext::beginFrame()
{
    BaseClass::beginFrame();
}

void SceneRenderContext::endFrame()
{
    BaseClass::endFrame();
}

}  // namespace haf::scene
