HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_VIEW_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_VIEW_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/math/types.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/render/render_data.hpp>

namespace haf::scene
{
class HAF_API SceneRenderContextView
{
public:
    math::Matrix4x4 const& cameraMatrix() const noexcept
    {
        return m_cameraMatrix();
    }

    math::Matrix4x4 const& modelViewMatrix() const noexcept
    {
        return m_currentModeViewMatrix();
    }

protected:
    SceneRenderContextView()  = default;
    ~SceneRenderContextView() = default;

    virtual void beginFrame() { m_cameraMatrix.resetHasChanged(); }
    virtual void endFrame() {}

    time::TimePoint m_nowFrame{};
    prop::PropertyState<fmath::Matrix4x4> m_cameraMatrix{};
    prop::PropertyState<fmath::Matrix4x4> m_currentModeViewMatrix{};
    render::FrameRenderStartData m_frame_render_start_data;
    render::FrameRenderData m_frame_render_data;
};
}  // namespace haf::scene

#endif
