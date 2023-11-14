#include <haf/include/scene/scene_render_context.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/color.hpp>

using namespace fmath;
using namespace haf::time;

namespace haf::scene
{
SceneRenderContext::SceneRenderContext()  = default;
SceneRenderContext::~SceneRenderContext() = default;

void SceneRenderContext::init()
{
    m_backgroundColor = colors::DarkGreen;
}

void SceneRenderContext::setNowFrame(TimePoint time_point)
{
    m_nowFrame = core::move(time_point);
}

void SceneRenderContext::setBackgroundColor(
    vector4df const& backgroundColor) noexcept
{
    m_backgroundColor = backgroundColor;
}

void SceneRenderContext::setCameraMatrix(Matrix4x4 const& camera_matrix)
{
    m_cameraMatrix = camera_matrix;
}

void SceneRenderContext::setCurrentModelViewMatrix(
    Matrix4x4 const& matrix) noexcept
{
    m_currentModeViewMatrix = matrix;
}

void SceneRenderContext::getOrUpdateRenderDataIndex(
    core::size_type& index,
    render::RenderData*& render_data) noexcept
{
    if (render_data == nullptr)
    {
        index = m_render_data.size();
        m_render_data.emplace_back();
        render_data = &(m_render_data.back());
    }
}

void SceneRenderContext::beginFrame()
{
    BaseClass::beginFrame();
    m_render_data.clear();
}

void SceneRenderContext::endFrame()
{
    BaseClass::endFrame();
}

}  // namespace haf::scene
