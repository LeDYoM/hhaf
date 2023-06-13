HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_VIEW_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_VIEW_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/properties/property_state.hpp>

namespace haf::scene
{
class HAF_API SceneRenderContextView
{
public:
    math::Matrix4x4 const& cameraMatrix() const noexcept
    {
        return m_cameraMatrix();
    }

    fmath::vector4df const& backgroundColor() const noexcept
    {
        return m_backgroundColor;
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
    prop::PropertyState<math::Matrix4x4> m_cameraMatrix{};
    prop::PropertyState<math::Matrix4x4> m_currentModeViewMatrix{};
    fmath::vector4df m_backgroundColor;
};
}  // namespace haf::scene

#endif
