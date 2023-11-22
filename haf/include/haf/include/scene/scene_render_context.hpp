HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <facil_math/include/matrix4x4.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/scene/scene_render_context_view.hpp>

namespace haf::scene
{
class HAF_API SceneRenderContext : public SceneRenderContextView
{
private:
    using BaseClass = SceneRenderContextView;

protected:
    SceneRenderContext();
    ~SceneRenderContext();

    virtual void init();

    void beginFrame() override;
    void endFrame() override;

    void setNowFrame(time::TimePoint time_point);
    void setBackgroundColor(fmath::vector4df const& backgroundColor) noexcept;

public:
    void getOrUpdateRenderDataIndex(core::size_type& index,
                                    render::RenderData*& render_data) noexcept;

    virtual void setCameraMatrix(fmath::Matrix4x4 const& matrix);
    void setCurrentModelViewMatrix(
        fmath::Matrix4x4 const& camera_matrix) noexcept;
};
}  // namespace haf::scene

#endif
