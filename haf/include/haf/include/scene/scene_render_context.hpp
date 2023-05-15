HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/scene/scene_render_context_view.hpp>

namespace haf::scene
{
class HAF_API SceneRenderContext : public SceneRenderContextView
{
private:
    using BaseClass = SceneRenderContextView;

protected:
    SceneRenderContext()  = default;
    ~SceneRenderContext() = default;

    void beginFrame() override;
    void endFrame() override;

    void setNowFrame(time::TimePoint time_point);

public:
    virtual void setCameraMatrix(math::Matrix4x4 const& matrix);
    void setCurrentModelViewMatrix(
        math::Matrix4x4 const& camera_matrix) noexcept;
};
}  // namespace haf::scene

#endif
