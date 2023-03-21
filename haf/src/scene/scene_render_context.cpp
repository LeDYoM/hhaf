#include <haf/include/scene/scene_render_context.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene
{
void SceneRenderContext::setNowFrame(time::TimePoint time_point)
{
    m_nowFrame = core::move(time_point);
}

void SceneRenderContext::setCameraMatrix(
    math::Matrix4x4 const& camera_matrix) noexcept
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
