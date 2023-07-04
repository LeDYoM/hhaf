HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_CONTEXT_FOR_SYSTEM_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_CONTEXT_FOR_SYSTEM_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/scene/scene_render_context.hpp>
#include <haf/include/system/isystem_provider.hpp>

namespace haf::scene
{
class HAF_API SceneRenderContextForSystem  : public SceneRenderContext
{
private:
    using BaseClass = SceneRenderContext;
public:
    explicit SceneRenderContextForSystem(sys::ISystemProvider& systemProvider);
    void beginFrame();
    void endFrame();

    void init() override;

    void setCameraMatrix(fmath::Matrix4x4 const& matrix) override;

private:
    sys::ISystemProvider& m_isystem_provider;
};
}  // namespace haf::scene

#endif
